#pragma once

// A struct that represents a rectangle that uses 32-bit integers
// to memorize the position in space
struct Rectangle
{
	int x, y, width, height;

public:
	Rectangle()
	{
		x = 0;
		y = 0;
		width = 0;
		height = 0;
	}

	Rectangle(int X, int Y, int Width, int Height)
	{
		x = X;
		y = Y;
		width = Width;
		height = Height;
	}

	~Rectangle()
	{ }


};