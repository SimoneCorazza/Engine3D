#include "Font.h"

#include <glm\glm.hpp>

// Border between the various glyphs in pixels
#define GLYPS_BORDER 5

// --- Static variables:

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
	Implementation note: some characters if translated as integers, instead of being positive (as it should)
	are negative, this because of the char that is signed. For this reason I convert the characters to unsigned char
	to have the values between 0 and 255 as they should be
	*/

	Char* c = new Char[strlen(C) + 1];
	int i = 0;
	while (C[i] != '\0')
	{
		c[i] = (unsigned char)C[i]; // Step from signed char to unsigned char to match unicode
		i++;
	}
	c[i] = '\0'; // Fine string character
	return c;
}

bool Font::Load(const char* TTFPath, const size_t Quality)
{
	quality = Quality;

	// --- FREE TYPE

	std::vector<std::vector<float>> bitmaps;
	std::vector<FT_ULong> chars;
	std::vector<glm::vec4> sizes;
	int maxGlyphHeight = 0; // Maximum height of a glyph in the font in pixels
	int wid = 0, hei = 0;
	int rows = 1; // Number of lines to make glyphs stand within the limits of the texture size

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

	// --- SCAN OF CHARACTERS SUPPORTED BY THE FONT

	FT_ULong charcode; // Currently selected font
	FT_UInt gindex; // Index of the current glyph

	int currentLine = 0; // Cursor used to know how many lines are used to store glyphs
	charcode = FT_Get_First_Char(face, &gindex);
	while (gindex != 0) // Flick the font characters
	{
		FT_Error errFT_loadGl = FT_Load_Glyph(face, gindex, FT_LOAD_NO_BITMAP); // Load the glyph
		if (errFT_loadGl != FT_Err_Ok)
			printf("Errore nel caricamento del simbolo: Car: %c; Cod: %i\n", charcode, (int)charcode);

		// I get the bitmap of the newly loaded glyph (face-> glyph)
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

				if (hei * rows > maxTextureSize) // In the event that not all characters can be in the texture
					return false;
			}
			maxGlyphHeight = glm::max(maxGlyphHeight, (int)face->glyph->bitmap.rows);

			bitmaps.insert(bitmaps.end(), bufferFloat); // I enter the glyph in the list
			chars.insert(chars.end(), charcode); // I enter the character
			sizes.insert(sizes.end(), glm::vec4(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap_top, face->glyph->bitmap_left)); // I enter the font size
		}

		charcode = FT_Get_Next_Char(face, charcode, &gindex);
	}

	// Calculating the size of the bitmap
	hei = maxGlyphHeight * rows; // Calculate the necessary height of the texture based on the maximum size of a font
								 // In the case in which you use more than one line the dimension is equal to the maximum possible, otherwise it is even
								 // at the position reached by the cursor
	wid = (rows == 1) ? currentLine : maxTextureSize;

	// --- OPENGL

	glGenTextures(1, &idTexture); // I create the texture id for the atlas
	glBindTexture(GL_TEXTURE_2D, idTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, wid, hei, 0, GL_RED, GL_FLOAT, nullptr);

	int x = 0;
	int y = 0;
	for (int i = 0; i < bitmaps.size(); i++) // Cycle to place glyphs in the texture
	{
		if (x > maxTextureSize)
		{
			x = 0;
			y += maxGlyphHeight + GLYPS_BORDER;
		}

		// I modify the portion of the textures needed
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, sizes[i].x, sizes[i].y, GL_RED, GL_FLOAT, &bitmaps[i][0]);

		GlyphInfo info;
		// Septum of the glyph uv
		info.areaUV = RectangleF((float)x / (float)wid, (float)y / (float)hei, (float)sizes[i].x / (float)wid, (float)sizes[i].y / (float)hei);
		info.width = (int)sizes[i].x;
		info.height = (int)sizes[i].y;
		info.bitmapTop = (int)sizes[i].z;
		info.bitmapLeft = (int)sizes[i].w;
		charactersMap[chars[i]] = info;

		x += sizes[i].x + GLYPS_BORDER; // I position myself for the next character
	}

	// GL_REPEAT is useless and can generate problems when glyphs are near the edges
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// Quality filters require the characters to be spaced (motif of the borders between the various glyphs) but guarantee one
	// better quality when they are rendered
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D); // I create the mipmaps for the desired filter
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
		return nullptr; // Case character not found
	else
		return &charactersMap.find(C)->second;
}