#pragma once

#include "PostProcessShader.hpp"

// Post process shader that makes the obteined frame in black and white
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

