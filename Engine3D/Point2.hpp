#pragma once

// Struct that represents a point in the 2D plane
struct Point2
{
	int x;
	int y;

	Point2()
	{ x = y = 0; }

	Point2(int X, int Y)
	{
		x = X;
		y = Y;
	}

	inline bool operator==(const Point2& b)
	{ 
		return x == b.x && y == b.y;
	}

	inline bool operator!=(const Point2& b)
	{
		return !(*this == b);
	}

	~Point2()
	{ }
};