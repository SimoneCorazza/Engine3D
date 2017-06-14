#include "LightScatteringPPS.h"

#include "DEBUG.h"
#include "LightScatteringPPSP.h"
#include "CommonConstants.h"

LightScatteringPPS::LightScatteringPPS()
{
}


LightScatteringPPS::~LightScatteringPPS()
{
}

void LightScatteringPPS::SetShaderParams(const PostProcessShaderParams* Params) const
{
	ASSERT(Params != nullptr, "Parms in LightScatteringPPS::SetShaderParams must not be null");
	//if(dynamic_cast<const LightScatteringPPSP*>(Params) == nullptr)
	//	Debug_ErrorBreak("Parms in LightScatteringPPS::SetShaderParams must be LightScatteringPPSP");

	const LightScatteringPPSP* p = (LightScatteringPPSP*)Params;

	glUniform1f(idExposure, p->getExposure());
	glUniform1f(idDecay, p->getDecay());
	glUniform1f(idDensity, p->getDensity());
	glUniform1f(idWeight, p->getWeight());

	glUniform2f(idLightPositionOnScreen, p->getScreenLightPos().x, p->getScreenLightPos().y);
}

void LightScatteringPPS::LoadIDVar()
{
	PostProcessShader::LoadIDVar();

	idExposure = GetVarID("exposure");
	idDensity = GetVarID("density");
	idDecay = GetVarID("decay");
	idWeight = GetVarID("weight");
	idLightPositionOnScreen = GetVarID("lightPositionOnScreen");
}
