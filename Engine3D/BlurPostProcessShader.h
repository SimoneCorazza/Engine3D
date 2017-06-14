#pragma once


#include "PostProcessShader.h"


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

