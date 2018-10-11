#include "MyColorActor.hpp"

#include "ColorShaderAP.hpp"
#include "UpdateParameters.hpp"
#include "Utility_Time.hpp"

MyColorActor::MyColorActor()
{
	param = new ColorShaderAP();
}


MyColorActor::~MyColorActor()
{
}

void MyColorActor::Update(const UpdateParameters & P)
{
	ColorShaderAP* p = (ColorShaderAP*)param;
	float value = abs(sinf(Utility_Time_GetTime()));
	p->color = glm::vec4(value, value, value, 1);
}
