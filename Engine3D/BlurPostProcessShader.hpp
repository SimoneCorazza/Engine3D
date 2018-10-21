#pragma once


#include "PostProcessShader.hpp"

// Post process shader that makes the obtained frame blurry
class BlurPostProcessShader : public PostProcessShader
{
	GLuint idResolution;

	public:
		BlurPostProcessShader();
		~BlurPostProcessShader();


	protected:

		void SetShaderParams(const PostProcessShaderParams* Params) const override;

		void LoadIDVar() override;
};

