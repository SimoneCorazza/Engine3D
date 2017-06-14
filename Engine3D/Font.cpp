#include "Font.h"

#include <glm\glm.hpp>

//Bordo tra i vari glifi in pixel
#define GLYPS_BORDER 5

//--- Variabili statiche:

FT_Library Font::freeType;
int Font::maxTextureSize;




Font::Font()
{
	idTexture = 0;
	quality = 0;
}


Font::~Font()
{

}







void Font::Inizialize()
{
	FT_Error err = FT_Init_FreeType(&freeType);
	if (err != FT_Err_Ok)
		printf("Errore nel caricamento della libreria: FreeType");

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
}

const Char* Font::ToChar(const char* C)
{
	/*
	Nota implementativa: Acuni caratteri se tradotti come interi invece di essere positivi (come dovrebbe)
	sono negativi questo a causa del char che è con segno per questa ragione converto i caratteri to unsigned char
	per avere i valori tra 0 e 255 come dovrebbero essere
	*/

	Char* c = new Char[strlen(C) + 1];
	int i = 0;
	while (C[i] != '\0')
	{
		c[i] = (unsigned char)C[i]; //Passo da signed char a unsigned char per avere la corrispondenza con unicode
		i++;
	}
	c[i] = '\0'; //Carattere fine stringa
	return c;
}

bool Font::Load(const char* TTFPath, const size_t Quality)
{
	quality = Quality;

	//--- FREE TYPE

	std::vector<std::vector<float>> bitmaps;
	std::vector<FT_ULong> chars;
	std::vector<glm::vec4> sizes;
	int maxGlyphHeight = 0; //Altezza massima di un glifo nel font in pixel 
	int wid = 0, hei = 0;
	int rows = 1; //Numero di righe per poter far stare i glifi nei limiti della dimensione della texture

	FT_Face face;
	FT_Error err = FT_New_Face(freeType, TTFPath, 0, &face);
	if (err != FT_Err_Ok)
	{
		printf("Errore %i nel caricamento del font:\n%s\n", err, TTFPath);
		return false;
	}

	err = FT_Set_Pixel_Sizes(face, quality, quality);
	if (err != FT_Err_Ok)
	{
		printf("Errore %i nel caricamento del font:\n%s\n", err, TTFPath);
		return false;
	}

	//--- SCANSIONE DEI CARATTERI SUPPORTATI DAL FONT

	FT_ULong charcode; //Carattere attualmente selezionato
	FT_UInt gindex; //Indice del glifo attuale

	int currentLine = 0; //Cursore utilizzato per poter sapere quante righe vengono utilizzate per memorizzare i glifi
	charcode = FT_Get_First_Char(face, &gindex);
	while (gindex != 0) //Scandaglio i caratteri del font
	{
		FT_Error errFT_loadGl = FT_Load_Glyph(face, gindex, FT_LOAD_NO_BITMAP); //Carico il glifo
		if (errFT_loadGl != FT_Err_Ok)
			printf("Errore nel caricamento del simbolo: Car: %c; Cod: %i\n", charcode, (int)charcode);

		//Ottengo la bitmap del glifo appena caricato (face->glyph)
		FT_Error errFT_renderBtm = FT_Render_Glyph(face->glyph, FT_Render_Mode::FT_RENDER_MODE_NORMAL);
		if (errFT_renderBtm != FT_Err_Ok)
			printf("Errore nella conversione del glifo in bitmap: Car: %c; Cod: %i\n", charcode, (int)charcode);

		std::vector<float> bufferFloat = std::vector<float>(face->glyph->bitmap.width * face->glyph->bitmap.rows);
		if (bufferFloat.size() != 0)
		{
			for (int j = 0; j < bufferFloat.size(); j++)
				bufferFloat[j] = (float)face->glyph->bitmap.buffer[j] / 255.0f;

			currentLine += face->glyph->bitmap.width + GLYPS_BORDER;
			if (currentLine > maxTextureSize)
			{
				rows++;
				currentLine = 0;

				if (hei * rows > maxTextureSize) //Nel caso in cui non tutti i caratteri possono stare nella texture
					return false;
			}
			maxGlyphHeight = glm::max(maxGlyphHeight, (int)face->glyph->bitmap.rows);

			bitmaps.insert(bitmaps.end(), bufferFloat); //Inserisco il glifo nell'elenco
			chars.insert(chars.end(), charcode); //Inserisco il carattere
			sizes.insert(sizes.end(), glm::vec4(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap_top, face->glyph->bitmap_left)); //Inserisco la dimensione del carattere
		}

		charcode = FT_Get_Next_Char(face, charcode, &gindex);
	}

	//Calcolo le dimensioni della bitmap
	hei = maxGlyphHeight * rows; //Calcolo l'altezza necessaria della texture in base alla dimensione massima di un carattere
								 //Nel caso in cui utilizzi più di una riga la dimensione è pari alla massima possibile, altrimenti è pari
								 //alla posizione raggiunta dal cursore
	wid = (rows == 1) ? currentLine : maxTextureSize;

	//--- OPENGL

	glGenTextures(1, &idTexture); //Genero l'id della texture per l'atlas
	glBindTexture(GL_TEXTURE_2D, idTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, wid, hei, 0, GL_RED, GL_FLOAT, nullptr);

	int x = 0;
	int y = 0;
	for (int i = 0; i < bitmaps.size(); i++) //Ciclo per posizionare li glifi nella texture
	{
		if (x > maxTextureSize)
		{
			x = 0;
			y += maxGlyphHeight + GLYPS_BORDER;
		}

		//Modifico la porzione dei texture necessaria
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, sizes[i].x, sizes[i].y, GL_RED, GL_FLOAT, &bitmaps[i][0]);

		GlyphInfo info;
		//Setto la coordinata delle uv del glifo
		info.areaUV = RectangleF((float)x / (float)wid, (float)y / (float)hei, (float)sizes[i].x / (float)wid, (float)sizes[i].y / (float)hei);
		info.width = (int)sizes[i].x;
		info.height = (int)sizes[i].y;
		info.bitmapTop = (int)sizes[i].z;
		info.bitmapLeft = (int)sizes[i].w;
		charactersMap[chars[i]] = info;

		x += sizes[i].x + GLYPS_BORDER; //Mi posiziono per il prossimo carattere
	}

	//GL_REPEAT è inutile e può generare problemi quando i glifi sono vicino ai bordi
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//Filtri di qualità richiedono che i caratteri siano distanziati (motivo dei bordi tra i vari glifi) ma garantiscono una
	//qualità migliore quando sono renderizzati
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D); //Genero le mipmap per il filtro desiderato
}




int Font::getQuality() const
{
	return quality;
}

GLuint Font::getIDTexture() const
{
	return idTexture;
}

const GlyphInfo* Font::getGlyphInfo(Char C) const
{
	auto p = charactersMap.find(C);
	if (p == charactersMap.end())
		return nullptr; //Caso carattere non trovato
	else
		return &charactersMap.find(C)->second;
}