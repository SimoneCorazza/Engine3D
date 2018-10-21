#include "SpriteFont.hpp"

#include "ShaderLoader.hpp"

#include "DEBUG.hpp"

// Characters that can be drawn at once (the more to render the more
// memory it takes)

#define MAX_CHAR_RENDER_ONCE 128

// Number of vertices per character to be rendered
#define NUM_VERTECES_FACE (4)

// Size in bytes of the vertex buffer
#define SIZE_VERTEX_BUFFER (sizeof(float) * NUM_VERTECES_FACE * 2 * MAX_CHAR_RENDER_ONCE)

// Size in bytes of the UV coordinate buffer
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

	Font::Inizialize(); // Initialize the font class
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



// @return Length of the string
int string_length(const Char* S)
{
	int i = 0;
	while (S[i] != '\0')
		i++;
	return i;
}

// Gets the size of the new line
// @param [in] Height - Height of the characters in a unit of measure
// @return Size of the new line
inline float GetNewLineSize(float Height)
{
	return Height + Height * 0.01f;
}

// Gets the size of the space character
// @param [in] Height - Height of the characters in a unit of measure
// @return Space font size
inline float GetSpaceSize(float Height)
{
	return Height * 0.5f;
}

// Gets the size of the character separator
// @param [in] Height - Height of the characters in a unit of measure
// @return Size of the separator between characters
inline float GetCharaterSeparetorSize(float Height)
{
	return Height * 0.08f;
}

void SpriteFont::Draw(const Char* String, const Font* Font, const glm::vec2& Location, const float& Height, const glm::vec4& Color)
{
	int len = string_length(String);
	if (String == nullptr || len == 0) // I avoid wasting time with a draw call if the string is empty
		return;

	ASSERT(Font != nullptr, "SpriteFont::Draw argument \"Font\" cannot be null");



	// Arrays for which to fill the UV and Vertex buffers (length is an estimate: they could be spaces '' or '\ n' that not
	// they go to generate characters and therefore coordinates by vertices or uv)
	// - !! NOTE !! - Better not to replace these two std::vector<float> with float array*
	// otherwise there are graphical glich (random black polygons) in the relays mode
	// this is probably due to the optimization of the delete of the arrays that provoke
	// a bad porting of the data on the VRAM
	std::vector<float> vertexCoords(NUM_VERTECES_FACE * 2 * len);
	std::vector<float> uvCoords(NUM_VERTECES_FACE * 2 * len);

	
	float pixel_hei = pixelScreenX * Height / screenX;

	glm::vec2 cursor = Location; // Cursor that indicates the current position of the next character to be rendered

	int indexChar = 0; // Current character
	int realChar = 0; // Counter of the characters that are rendered
	while (String[indexChar] != '\0') // Cycle to position each character on video with respective UV
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
				; // Case not found: I do not display anything
			else
			{
				// I make proportions to get the glyph pixels
				float rapporto = pixel_hei / (float)Font->getQuality();
				float h = (float)info->height *  rapporto;
				float w = (float)info->width  * rapporto;
				float top = (float)info->bitmapTop * rapporto;

				// Calculate the displacement at the bottom (by calculating it and then converting it to OpenGL coordinates)
				float sposY = (h - top) / pixelScreenY * screenY;
				float widChar = w / pixelScreenX * screenX; // Calculate the height of the character in coordinates for OpenGL
				float heiChar = h / pixelScreenY * screenY;

				int pos = NUM_VERTECES_FACE * 2 * realChar;

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

	if (realChar > 0) // I check that there is at least one character to render
	{
		// I enter data in the buffers:
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
			(void*)0            // offset buffer array
			);

		glEnableVertexAttribArray(idUVArray);
		glBindBuffer(GL_ARRAY_BUFFER, idBuffUV);
		glVertexAttribPointer(
			idUVArray,			// attribute ID
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // offset buffer array
			);

		glDrawArrays(GL_QUADS, 0, NUM_VERTECES_FACE * realChar);


		glDisableVertexAttribArray(idVertexArray);
		glDisableVertexAttribArray(idUVArray);
	}
}