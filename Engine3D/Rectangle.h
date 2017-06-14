#pragma once

//Struct che rappresenta un rettangolo che usa dei integer a 32 bit
//per memorizzare la posizione nello spazio
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