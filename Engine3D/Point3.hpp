#pragma once

#include "Point2.h"

// Struct that represents an internal point in 3D space
struct Point3
{
	int x;
	int y;
	int z;

	Point3()
	{
		x = y = z = 0;
	}

	Point3(int X, int Y, int Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	Point3(Point2 P, int Z)
	{
		x = P.x;
		y = P.y;
		z = Z;
	}

	inline bool operator==(const Point3& b)
	{
		return x == b.x && y == b.y && z == b.z;
	}

	inline bool operator!=(const Point3& b)
	{
		return !(*this == b);
	}

	~Point3()
	{ }
};

