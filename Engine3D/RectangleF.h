#pragma once

//Struct che rappresenta un rettangolo che usa dei float a 32 bit
//per memorizzare la posizione nello spazio
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