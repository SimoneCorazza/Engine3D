#pragma once

#include "RectangleF.hpp"

// Class that store the information about a glyph
class GlyphInfo
{
	// ATTRIBUTES:
public:
	// Area occupied by the character in the texture
	RectangleF areaUV;

	// X size of the texture
	int width;
	// Y size of the texture
	int height;

	int bitmapTop;
	int bitmapLeft;


	// MANUFACTURERS:
public:
	GlyphInfo();
	~GlyphInfo();


	// METHODS:
public:


};