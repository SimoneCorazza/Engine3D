#include "Light.h"

#define MIN_LIGHT 0.01f
#define MAXIMUM_RADIUS 100 //Raggio massimo di una generica luce

//Light::Light(unsigned int ID, Scene* Scene)
//	: ItemScene(ID, Scene)
//{
//	state = true;
//}

Light::Light()
{
	state = true;
}



Light::~Light()
{
}



bool Light::isDirectional()
{
	return position.w == 0;
}

const glm::vec3 & Light::getPosition()
{
	return glm::vec3(position);
}

float Light::getClippingRadius()
{
	//Una fonte usata ma non perfetta: http://gamedev.stackexchange.com/questions/56897/glsl-light-attenuation-color-and-intensity-formula

	if (isDirectional())
		return 100; //return sqrtf(1.0f / quadraticAttenuation * MIN_LIGHT); //Approssimo il raggio della sfera
	else
		return FLT_MAX; //Nel caso sia una luce direzionale (es. sole)
}
