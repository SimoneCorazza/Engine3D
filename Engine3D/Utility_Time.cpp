#include "Utility_Time.h"

#include <GLFW\glfw3.h>

float Utility_Time_GetTime()
{
	return (float)glfwGetTime();
}
