#pragma once

#include <GL\glew.h>
#include <map>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "GlyphInfo.hpp"
typedef FT_ULong Char;

class SpriteFont;

// Class that represents a font
class Font
{
	friend SpriteFont;

	// FreeType library
	static FT_Library freeType;

	// Maximum pixel size supported by the device used
	static int maxTextureSize;

	// ID of the texture according to OpenGL containing the character atlas
	GLuint idTexture;

	// Match the corresponding descriptor to each character
	std::map<Char, GlyphInfo> charactersMap;

	// Quality chosen for the font (used only if .ttf)
	size_t quality;


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
	// @NOTE Method created to be accessed only by the "SpriteFont" class
	static void Inizialize();

	// METHODS:
public:

	// Allows you to upload a .ttf file containing information about the catatter set
	// @param [in] TTFPath - Path to the .ttf file
	// @param [in] Quality - Coefficient representing the quality (a higher number means better quality)
	// @return True if the upload was successful, Flase otherwise
	// The upload is successful if:
	// • The FreeType library is not error-free
	// • Font characters are in a texture
	bool Load(const char* TTFPath, const size_t Quality);

	// Gets the ID of the texture containing the glyphs atlas
	GLuint getIDTexture() const;

	// Gets the quality used to make this font (if .ttf)
	int getQuality() const;

	// Gets the portion of texture containing the indicated character
	// If the character is not present, it returns null
	const GlyphInfo* getGlyphInfo(Char C) const;
};