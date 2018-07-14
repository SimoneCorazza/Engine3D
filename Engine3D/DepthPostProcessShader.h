#pragma once

#include "PostProcessShader.h"

// Post process shader to display the depth buffer (Use for debugging)
class DepthPostProcessShader : public PostProcessShader
{
	public:
		DepthPostProcessShader();
		~DepthPostProcessShader();

	protected:

		void SetShaderParams(const PostProcessShaderParams* Params) const override;

		void LoadIDVar() override;
};

