#include "Draw2D.h"

#include <GLFW\glfw3.h>
#include <glm\gtc\matrix_transform.hpp>
#include "DEBUG.h"

Draw2D::Draw2D()
{
}


Draw2D::~Draw2D()
{
}




void Draw2D::Inizialize()
{
	GLFWmonitor* m = glfwGetPrimaryMonitor();
	glfwGetMonitorPhysicalSize(m, &monitorMM.x, &monitorMM.y);

	ASSERT(monitorMM.x > 0 && monitorMM.y > 0, "Draw2D::Inizialize() Monitor size is 0");

	const GLFWvidmode* v = glfwGetVideoMode(m);
	resolution.x = v->width;
	resolution.y = v->height;

	sf.Inizialize(); //Inizializzo la classe per il rendering dei caratteri
}

void Draw2D::SetWindowSize(float Width, float Height)
{
	windowSizeMM.x = (int)( Width / (float)resolution.x * (float)monitorMM.x );
	windowSizeMM.y = (int)( Height / (float)resolution.y * (float)monitorMM.y );
	matrix = glm::ortho(0.f, (float)windowSizeMM.x, (float)windowSizeMM.y, 0.f, -1.f, 1.f);

	sf.SetSizes(Width, Height, windowSizeMM.x, windowSizeMM.y);
	sf.SetMatrix(matrix);
}

void Draw2D::DrawText(const char* String, const Font* Font, const Point2& Location, size_t Height, const glm::vec4 & Color)
{
	const Char* c = Font::ToChar(String);
	sf.Draw(c, Font, glm::vec2(Location.x, Location.y), (float)Height, Color);
	delete c; //Rilascio l'array di caratteri convertito
}
