#pragma once

#include <glm\glm.hpp>

// Struct representing a plane
struct Plane
{
	float a, b, c, d;

	Plane()
	{
		a = 0;
		b = 0;
		c = 0;
		d = 0;
	}

	void Normalize()
	{
		float mag = glm::sqrt(a * a + b * b + c * c);
		a /= mag;
		b /= mag;
		c /= mag;
		d /= mag;
	}
};