#include "BlurPostProcessShader.hpp"

#include "PostProcessShaderParams.hpp"
#include "DEBUG.hpp"

BlurPostProcessShader::BlurPostProcessShader()
{
}


BlurPostProcessShader::~BlurPostProcessShader()
{
}


void BlurPostProcessShader::SetShaderParams(const PostProcessShaderParams* Params) const
{
	ASSERT(Params != nullptr, "Parms in BlurPostProcessShader::SetShaderParams must not be null");
	glUniform2f(idResolution, Params->getResolution().x, Params->getResolution().y);
}

void BlurPostProcessShader::LoadIDVar()
{
	PostProcessShader::LoadIDVar(); // I call the base method
	idResolution = GetVarID("resolution");
}