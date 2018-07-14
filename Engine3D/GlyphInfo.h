#pragma once

#include "RectangleF.h"

// Class that allows you to store all the various information about a glyph
class GlyphInfo
{
	// ATTRIBUTES:
public:
	RectangleF areaUV; // Area occupied by the character in the texture

	int width; // X size of the texture
	int height; // Y-size of the texture
	int bitmapTop;
	int bitmapLeft;


	// MANUFACTURERS:
public:
	GlyphInfo();
	~GlyphInfo();


	// METHODS:
public:


};