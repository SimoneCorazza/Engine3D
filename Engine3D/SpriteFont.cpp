#include "SpriteFont.h"

#include "ShaderLoader.h"

#include "DEBUG.h"

//Caratteri che è possibile disegnare in una sola volta (richiede una maggiore memoria)
#define MAX_CHAR_RENDER_ONCE 128
//Numero di vertici per carattere da renderizzare
#define NUM_VERTECES_FACE (4)
//Dimensione in byte del buffer dei vertici
#define SIZE_VERTEX_BUFFER (sizeof(float) * NUM_VERTECES_FACE * 2 * MAX_CHAR_RENDER_ONCE)
//Dimensione in byte del buffer delle coordinate UV
#define SIZE_UV_BUFFER (sizeof(float) * NUM_VERTECES_FACE * 2 * MAX_CHAR_RENDER_ONCE)


GLuint SpriteFont::idShader;

GLuint SpriteFont::idBuffVerteces;
GLuint SpriteFont::idBuffUV;

GLuint SpriteFont::idSampler;
GLuint SpriteFont::idColor;
GLuint SpriteFont::idMatrix;

GLuint SpriteFont::idVertexArray;
GLuint SpriteFont::idUVArray;

float SpriteFont::pixelScreenX = 0;
float SpriteFont::pixelScreenY = 0;

float SpriteFont::screenX = 0;
float SpriteFont::screenY = 0;



SpriteFont::SpriteFont()
{
}


SpriteFont::~SpriteFont()
{
}





void SpriteFont::Inizialize()
{
	GLuint ids[2];
	glGenBuffers(2, ids);
	idBuffVerteces = ids[0];
	idBuffUV = ids[1];

	glBindBuffer(GL_ARRAY_BUFFER, idBuffVerteces);
	glBufferData(GL_ARRAY_BUFFER, SIZE_VERTEX_BUFFER, nullptr, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, idBuffUV);
	glBufferData(GL_ARRAY_BUFFER, SIZE_UV_BUFFER, nullptr, GL_STREAM_DRAW);

	idShader = ShaderLoader::LoadShader("Caratteri.vert.glsl", "Caratteri.frag.glsl");

	glUseProgram(idShader);

	idColor = glGetUniformLocation(idShader, "color");
	idSampler = glGetUniformLocation(idShader, "textureCarattere");
	idMatrix = glGetUniformLocation(idShader, "MVP");

	idVertexArray = glGetAttribLocation(idShader, "vertex");
	idUVArray = glGetAttribLocation(idShader, "coordUV");

	Font::Inizialize(); //Inizializzo la classe dei font
}

void SpriteFont::SetSizes(float PixelScreenX, float PixelScreenY, float ScreenX, float ScreenY)
{
	SpriteFont::pixelScreenX = PixelScreenX;
	SpriteFont::pixelScreenY = PixelScreenY;

	SpriteFont::screenX = ScreenX;
	SpriteFont::screenY = ScreenY;
}

void SpriteFont::SetMatrix(const glm::mat4 & M)
{
	glUseProgram(idShader);
	glUniformMatrix4fv(idMatrix, 1, GL_FALSE, &M[0][0]);
}



//@return Lunghezza della stringa
int string_length(const Char* S)
{
	int i = 0;
	while (S[i] != '\0')
		i++;
	return i;
}

//Ottiene la dimensione della nuova righa
//@param[in] Height - Altezza dei caratteri in una unità di misura
//@return Dimensione della nuova riga
inline float GetNewLineSize(float Height)
{
	return Height + Height * 0.01f;
}

//Ottiene la dimensione del carattere spazio
//@param[in] Height - Altezza dei caratteri in una unità di misura
//@return Dimensione del carattere spazio
inline float GetSpaceSize(float Height)
{
	return Height * 0.5f;
}

//Ottiene la dimensione del separatore dei caratteri
//@param[in] Height - Altezza dei caratteri in una unità di misura
//@return Dimensione del separatore tra caratteri
inline float GetCharaterSeparetorSize(float Height)
{
	return Height * 0.08f;
}

void SpriteFont::Draw(const Char* String, const Font* Font, const glm::vec2& Location, const float& Height, const glm::vec4& Color)
{
	int len = string_length(String);
	if (String == nullptr || len == 0) //Evito di perdere tempo con una draw call nel caso la tringa sia vuota
		return;

	ASSERT(Font != nullptr, "SpriteFont::Draw argument \"Font\" cannot be null");



	//Array per con cui riempire i buffer delle UV e dei Vertici (la lunghezza è una stima: pottrebbero essere spazi ' ' o '\n' che non
	//vanno a generare caratteri e dunque coordinate per vertici o uv)
	//-!!NOTA!!-- Meglio non sostituire questi due std::vector<float> con array float*
	//altrimenti ci sono dei glich grafici (poligoni neri random) nella modalità relese
	//questo probabilmente è dovuto al fatto che vengono ottimizzate le operazioni di delete degli array che provoca un cattivo
	//porting degli array nella VRAM
	std::vector<float> vertexCoords(NUM_VERTECES_FACE * 2 * len);
	std::vector<float> uvCoords(NUM_VERTECES_FACE * 2 * len);

	
	float pixel_hei = pixelScreenX * Height / screenX;

	glm::vec2 cursor = Location; //Cursore che indica la posizione attuale del prossimo carattere da renderizzare

	int indexChar = 0; //Carattere attuale
	int realChar = 0; //Contatore dei caratteri che vengono renderizzati
	while (String[indexChar] != '\0') //Ciclo per posizionare ogni carattere a video con rispettive UV
	{
		if (String[indexChar] == ' ')
			cursor.x += GetSpaceSize(Height);
		else if (String[indexChar] == '\n')
		{
			cursor.y += GetNewLineSize(Height);
			cursor.x = Location.x;
		}
		else
		{
			const GlyphInfo* info = Font->getGlyphInfo(String[indexChar]);

			if (info == nullptr)
				; //Caso carattere non trovato: non visualizzo nulla
			else
			{
				//Faccio delle proporzioni per ottenere i pixel del glifo
				float rapporto = pixel_hei / (float)Font->getQuality();
				float h = (float)info->height *  rapporto;
				float w = (float)info->width  * rapporto;
				float top = (float)info->bitmapTop * rapporto;

				//Calcolo lo spostamento in basso (calcolandolo e poi convertendolo in coordinate di OpenGL)
				float sposY = (h - top) / pixelScreenY * screenY;
				float widChar = w / pixelScreenX * screenX; //Calcolo l'altezza del carattere in coordinate per OpenGL
				float heiChar = h / pixelScreenY * screenY;

				int pos = NUM_VERTECES_FACE * 2 * realChar;

				//float x1 = cursor.x, x2 = cursor.x + widChar, y1 = cursor.y + Height - heiChar + sposY, y2 = cursor.y + Height + sposY;
				float x1 = cursor.x, x2 = cursor.x + widChar, y1 = cursor.y + Height - heiChar + sposY, y2 = cursor.y + Height + sposY;

				vertexCoords[pos + 0] = x1;
				vertexCoords[pos + 1] = y1;

				vertexCoords[pos + 2] = x1;
				vertexCoords[pos + 3] = y2;

				vertexCoords[pos + 4] = x2;
				vertexCoords[pos + 5] = y2;

				vertexCoords[pos + 6] = x2;
				vertexCoords[pos + 7] = y1;


				float u1 = info->areaUV.x, u2 = info->areaUV.x + info->areaUV.width, v1 = info->areaUV.y, v2 = info->areaUV.y + info->areaUV.height;

				uvCoords[pos + 0] = u1;
				uvCoords[pos + 1] = v1;

				uvCoords[pos + 2] = u1;
				uvCoords[pos + 3] = v2;

				uvCoords[pos + 4] = u2;
				uvCoords[pos + 5] = v2;

				uvCoords[pos + 6] = u2;
				uvCoords[pos + 7] = v1;


				cursor.x += widChar + GetCharaterSeparetorSize(Height);
				realChar++;
			}
		}

		indexChar++;
	}

	if (realChar > 0) //Controllo che ci sia almeno un carattere da renderizzare
	{
		//Inserisco i dati nei buffer:
		glBindBuffer(GL_ARRAY_BUFFER, idBuffVerteces);
		glBufferData(GL_ARRAY_BUFFER, SIZE_VERTEX_BUFFER, nullptr, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * NUM_VERTECES_FACE * 2 * realChar, &vertexCoords[0]);

		glBindBuffer(GL_ARRAY_BUFFER, idBuffUV);
		glBufferData(GL_ARRAY_BUFFER, SIZE_UV_BUFFER, nullptr, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * NUM_VERTECES_FACE * 2 * realChar, &uvCoords[0]);

		glUseProgram(idShader);

		glUniform4f(idColor, Color.r, Color.g, Color.b, Color.a);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Font->getIDTexture());
		glUniform1i(idSampler, 0);

		glEnableVertexAttribArray(idVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, idBuffVerteces);
		glVertexAttribPointer(
			idVertexArray,      // attribute ID
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		glEnableVertexAttribArray(idUVArray);
		glBindBuffer(GL_ARRAY_BUFFER, idBuffUV);
		glVertexAttribPointer(
			idUVArray,			// attribute ID
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		glDrawArrays(GL_QUADS, 0, NUM_VERTECES_FACE * realChar);


		glDisableVertexAttribArray(idVertexArray);
		glDisableVertexAttribArray(idUVArray);
	}
}