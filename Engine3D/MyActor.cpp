#include "MyActor.hpp"

#include "LiftTriAP.hpp"
#include "UpdateParameters.hpp"
#include "Utility_Time.hpp"

#include <GLFW\glfw3.h>

MyActor::MyActor()
{
	
}


MyActor::~MyActor()
{
}



void MyActor::Update(const UpdateParameters& P)
{
	const float SPEED = .1f;

	float mX;
	if (P.getInputState()->IsKeyPressed(GLFW_KEY_UP))
	{
		mX = 1;
	}
	else if (P.getInputState()->IsKeyPressed(GLFW_KEY_DOWN))
	{
		mX = -1;
	}
	else
	{
		mX = 0;
	}

	float mZ;
	if (P.getInputState()->IsKeyPressed(GLFW_KEY_LEFT))
	{
		mZ = 1;
	}
	else if (P.getInputState()->IsKeyPressed(GLFW_KEY_RIGHT))
	{
		mZ = -1;
	}
	else
	{
		mZ = 0;
	}

	glm::vec3 moveX = mX * glm::vec3(1, 0, 0) * SPEED;
	glm::vec3 moveZ = mZ * glm::vec3(0, 0, 1) * SPEED;

	setLocation(getLocation() + moveX + moveZ);
}
