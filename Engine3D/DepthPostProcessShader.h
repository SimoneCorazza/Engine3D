#pragma once

#include "PostProcessShader.h"

//Post process shader per visualizzare il depth buffer (Utilizzo per il debug)
class DepthPostProcessShader : public PostProcessShader
{
	public:
		DepthPostProcessShader();
		~DepthPostProcessShader();

	protected:

		void SetShaderParams(const PostProcessShaderParams* Params) const override;

		void LoadIDVar() override;
};

