#pragma once

#include "PostProcessShader.h"

// Post process shader that makes the image in black and white
class BlackAndWhitePostProcessShader : public PostProcessShader
{

	public:
		BlackAndWhitePostProcessShader();
		~BlackAndWhitePostProcessShader();

	public:

	protected:

		void SetShaderParams(const PostProcessShaderParams* Params) const override;

		void LoadIDVar() override;
};

