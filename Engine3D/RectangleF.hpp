#pragma once

// Struct that represents a rectangle that uses 32-bit floats
// to memorize the position in space
struct RectangleF
{
	float x, y, width, height;

	public:
		RectangleF()
		{
			x = 0;
			y = 0;
			width = 0;
			height = 0;
		}

		RectangleF(float X, float Y, float Width, float Height)
		{
			x = X;
			y = Y;
			width = Width;
			height = Height;
		}

		~RectangleF()
		{ }


};