#pragma once

#include <GL\glew.h>
#include <map>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "GlyphInfo.h"

typedef FT_ULong Char;

// Enumeration that allows to identify
enum FontAtlas_Descriptor
{
	FontAtlas_Descriptor_PersonalStandard
};

class SpriteFont;

// Class that represents a font
class Font
{
	friend SpriteFont;

	static FT_Library freeType; // FreeType library
	static int maxTextureSize; // Maximum pixel size supported by the device used

	GLuint idTexture; // ID of the texture according to OpenGL containing the character atlas
	std::map<Char, GlyphInfo> charactersMap; // Match the corresponding descriptor to each character
	size_t quality; // Quality chosen for the font (used only if .ttf)


public:
	Font();
	~Font();


	// STATIC METHODS:
public:

	// Convert a string with ascii characters to unicode characters
	// @param [in] C - Characters to be converted
	// @return Sequence of unicode characters
	// @NOTA is up to the user to delete the returned array
	static const Char* ToChar(const char* C);

private:

	// Initialize the Free Type library and variables
	// static of the class
	// @friend Method created to be accessed only by the "SpriteFont" lcasse
	static void Inizialize();

	// METHODS:
public:

	// Allows you to upload a .ttf file containing information about the catatter set
	// @param [in] TTFPath - Path to the .ttf file
	// @param [in] Quality - Coefficient representing the quality (the higher the higher the quality)
	// @return True if the upload was successful, Flase otherwise
	// The upload is successful if:
	// • The FreeType library is not error-free
	// • Font characters are in a texture
	bool Load(const char* TTFPath, const size_t Quality);

	// Allows you to load a texture atlas of characters to use as a font
	// @param [in] AtlasPath - Path to the image of the atlas of the characters
	// @param [in] DescriptorPath - Path of the descriptor of the atlas (indicates the position of the characters in the image)
	// @param [in] Type - Indicates the format of the descriptor
	void Load(const char* AtlasPath, const char* DescrittorePath, FontAtlas_Descriptor Type);

	// Gets the ID of the texture containing the glyphs atlas
	GLuint getIDTexture() const;

	// Gets the quality used to make this font (if .ttf)
	int getQuality() const;

	// Gets the portion of texture containing the indicated character
	// If the character is not present, it returns null
	const GlyphInfo* getGlyphInfo(Char C) const;
};