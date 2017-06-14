#pragma once
#include "PostProcessShaderParams.h"

//Classe per i parametri dell'effetto post process light scattering
class LightScatteringPPSP : public PostProcessShaderParams
{
	glm::vec2 screenLightPos; //Posizione della luce a schermo
	float exposure;
	float decay;
	float density;
	float weight;


	public:
		LightScatteringPPSP();
		~LightScatteringPPSP();

	public:

		glm::vec2 getScreenLightPos() const;
		void setScreenLightPos(glm::vec2 P);

		float getExposure() const;
		void setExposure(float E);

		float getDecay() const;
		void setDecay(float D);

		float getDensity() const;
		void setDensity(float D);

		float getWeight() const;
		void setWeight(float W);
};

