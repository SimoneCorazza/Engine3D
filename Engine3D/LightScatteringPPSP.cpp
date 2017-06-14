#include "LightScatteringPPSP.h"



LightScatteringPPSP::LightScatteringPPSP()
{
	exposure = 0;
	decay = 0;
	density = 0;
	weight = 0;
}


LightScatteringPPSP::~LightScatteringPPSP()
{
}



glm::vec2 LightScatteringPPSP::getScreenLightPos() const
{
	return screenLightPos;
}

void LightScatteringPPSP::setScreenLightPos(glm::vec2 P)
{
	screenLightPos = P;
}

float LightScatteringPPSP::getExposure() const
{
	return exposure;
}

void LightScatteringPPSP::setExposure(float E)
{
	exposure = E;
}

float LightScatteringPPSP::getDecay() const
{
	return decay;
}

void LightScatteringPPSP::setDecay(float D)
{
	decay = D;
}

float LightScatteringPPSP::getDensity() const
{
	return density;
}

void LightScatteringPPSP::setDensity(float D)
{
	density = D;
}

float LightScatteringPPSP::getWeight() const
{
	return weight;
}

void LightScatteringPPSP::setWeight(float W)
{
	weight = W;
}
