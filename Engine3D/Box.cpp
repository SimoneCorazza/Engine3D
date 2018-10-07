#include "Box.hpp"

/*
Axis:
 ^
Z|
 |
 O------>     (Y exit upwords from the screen)
Y      X
Bottom part:						Top part:
	V1--------V4					V5--------V8
	|		  |						|		  |
	|		  |						|		  |
	V2--------V3					V6--------V7
*/


Box::Box()
{

}


Box::Box(float Width, float Height, float Depth)
{
	float x2 = Width / 2.0f;
	float y2 = Height / 2.0f;
	float z2 = Depth / 2.0f;
	
	v1.x = -x2; v1.y = -y2; v1.z = z2;
	v2.x = -x2; v2.y = -y2; v2.z = -z2;
	v3.x = x2; v3.y = -y2; v3.z = -z2;
	v4.x = x2; v4.y = -y2; v4.z = z2;

	v5.x = -x2; v5.y = y2; v5.z = z2;
	v6.x = -x2; v6.y = y2; v6.z = -z2;
	v7.x = x2; v7.y = y2; v7.z = -z2;
	v8.x = x2; v8.y = y2; v8.z = z2;
}

Box::Box(float MaxX, float MinX, float MaxY, float MinY, float MaxZ, float MinZ)
{
	v1.x = MinX; v1.y = MinY; v1.z = MaxZ;
	v2.x = MinX; v2.y = MinY; v2.z = MinZ;
	v3.x = MaxX; v3.y = MinY; v3.z = MinZ;
	v4.x = MaxX; v4.y = MinY; v4.z = MaxZ;

	v5.x = MinX; v5.y = MaxY; v5.z = MaxZ;
	v6.x = MinX; v6.y = MaxY; v6.z = MinZ;
	v7.x = MaxX; v7.y = MaxY; v7.z = MinZ;
	v8.x = MaxX; v8.y = MaxY; v8.z = MaxZ;
}

Box::~Box()
{
}

const glm::vec3 & Box::getV1() const
{
	return v1;
}

const glm::vec3 & Box::getV2() const
{
	return v2;
}

const glm::vec3 & Box::getV3() const
{
	return v3;
}

const glm::vec3 & Box::getV4() const
{
	return v4;
}

const glm::vec3 & Box::getV5() const
{
	return v5;
}

const glm::vec3 & Box::getV6() const
{
	return v6;
}

const glm::vec3 & Box::getV7() const
{
	return v7;
}

const glm::vec3 & Box::getV8() const
{
	return v8;
}
