#pragma once

#include "PostProcessShader.h"

//Post process shader che rende l'immagine in bianco e nero
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

