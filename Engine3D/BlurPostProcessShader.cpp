#include "BlurPostProcessShader.h"

#include "PostProcessShaderParams.h"
#include "DEBUG.h"

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
	PostProcessShader::LoadIDVar(); // I call the basic method
	idResolution = GetVarID("resolution");
}