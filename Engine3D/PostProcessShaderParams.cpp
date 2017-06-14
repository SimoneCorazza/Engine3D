#include "PostProcessShaderParams.h"

#include <GLFW\glfw3.h>


PostProcessShaderParams::PostProcessShaderParams()
{
	
}


PostProcessShaderParams::~PostProcessShaderParams()
{
}

void PostProcessShaderParams::setResolution(const glm::vec2 & R)
{
	resolution = R;
}

glm::vec2 PostProcessShaderParams::getResolution() const
{
	return resolution;
}

float PostProcessShaderParams::getCurrentTime()
{
	return (float)glfwGetTime();
}
