#include "Utility_Time.hpp"

#include <GLFW\glfw3.h>

float Utility_Time_GetTime()
{
	return (float)glfwGetTime();
}
