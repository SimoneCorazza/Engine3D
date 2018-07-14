#pragma once
#include "PostProcessShader.h"

// Class representing the post process shader for light scattering or god rays
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

		// Method to derive that allows you to set the parameters
		// @param [in] Params - Parameters for the shader
		virtual void SetShaderParams(const PostProcessShaderParams* Params) const override;

		void LoadIDVar() override;
};

