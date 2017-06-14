#pragma once
#include "PostProcessShader.h"

//Classe che rappresenta lo shader post process per il light scattering o god rays
class LightScatteringPPS : public PostProcessShader
{
	GLuint idExposure;
	GLuint idDecay;
	GLuint idDensity;
	GLuint idWeight;

	GLuint idLightPositionOnScreen;

	public:
		LightScatteringPPS();
		~LightScatteringPPS();


	protected:

		//Metodo da derivare che consente di impostare i parametri
		//@param[in] Params - Parametri per lo shader
		virtual void SetShaderParams(const PostProcessShaderParams* Params) const override;

		void LoadIDVar() override;
};

