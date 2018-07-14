#pragma once

#include "SpriteFont.h"
#include "Point2.h"

// Class used for the 2D drawing of the interface
class Draw2D
{
	Point2 monitorMM; // Size of the main monitor in millimeters
	Point2 resolution; // Resolution currently used for the monitor
	Point2 windowSizeMM; // Window size in millimeters
	glm::mat4 matrix; // 2D matrix for vertex calculation

	SpriteFont sf; // Class used for rendering characters



	public:
		Draw2D();
		~Draw2D();

	public:

		// Initialize the class
		void Inizialize();

		// Set the screen size
		// @param [in] Width - Size (X) of the window in pixels
		// @param [in] Height - Size (Y) of the window in pixels
		void SetWindowSize(float Width, float Height);

		// Draw the string with the chosen font
		// @param [in] String - String to render
		// @param [in] Font - Font to use
		// @param [in] Location - Location from which to draw the font in millimeters
		// @param [in] Height - Height of the characters in millimeters
		// @param [in] Color - Color to use for the font
		// @NOTE If a character is not present in the font it is ignored
		void DrawText(const char* String, const Font* Font, const Point2& Location, size_t Height, const glm::vec4& Color);
};

