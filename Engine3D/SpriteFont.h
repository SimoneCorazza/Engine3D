#pragma once

#include <glm\glm.hpp>

#include "Font.h"


// Static class that allows you to render fonts on video
class SpriteFont
{
	// Buffers:

	static GLuint idBuffVerteces; // Buffer for the vertices
	static GLuint idBuffUV; // Buffer for UV coordinates

							// Shader variables:
	static GLuint idShader;

	// Uniform:
	static GLuint idColor;
	static GLuint idSampler;
	static GLuint idMatrix;

	// attribs:
	static GLuint idVertexArray;
	static GLuint idUVArray;

	// Dimensions:
	static float pixelScreenX;
	static float pixelScreenY;

	static float screenX;
	static float screenY;

public:
	SpriteFont();
	~SpriteFont();

public:

	// Initialize the sprite font
	void Inizialize();

	// Set the second screen size
	// @param [in] PixelScreenX - Size (X) of the window in pixels
	// @param [in] PixelScreenY - Size (Y) of the window in pixels
	// @param [in] ScreenX - Dimension (X) of the window in selected geometric units (must correspond with those of the matrix)
	// @param [in] ScreenY - Size (Y) of the window in selected geometric units (must correspond with those of the matrix)
	void SetSizes(float PixelScreenX, float PixelScreenY, float ScreenX, float ScreenY);

	// Set the array to position the vertices of the spritefont
	void SetMatrix(const glm::mat4& M);

	// It allows to start a sequence of font drawings
	void Begin();

	// Forward the string design request with the chosen font
	// must be included between Begin () and End ()
	// @param [in] String - String to render
	// @param [in] Font - Font to use
	// @param [in] Location - Location from which to draw the font
	// @param [in] Height - Desired font size
	// @param [in] Color - Color to use for the font
	void RequestDraw(const Char* String, const Font& Font, const glm::vec2& Location, const float& Height, const glm::vec4& Color);

	// It allows to conclude the sequence of drawing requests and to render them
	void End();

	// Draw the string with the chosen font
	// @param [in] String - String to render
	// @param [in] Font - Font to use
	// @param [in] Location - Location from which to draw the font in millimeters
	// @param [in] Height - Height of the characters in millimeters
	// @param [in] Color - Color to use for the font
	// @NOTE If a character is not present in the font it is ignored
	void Draw(const Char* String, const Font* Font, const glm::vec2& Location, const float& Height, const glm::vec4& Color);
};

