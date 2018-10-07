#include "LiftTriShader.hpp"

#include "Model.hpp"
#include "Material.hpp"
#include "Texture2D.hpp"

#include "LiftTriAP.hpp"


LiftTriShader::LiftTriShader()
{
	idMatrix = 0;
	idTextureSampler = 0;
	idDelta = 0;
	bothSide = true;
}


LiftTriShader::~LiftTriShader()
{
}



void LiftTriShader::LoadIDVar()
{
	idMatrix = GetVarID("MVP");
	idTextureSampler = GetVarID("textureSampler");
	idDelta = GetVarID("delta");

	idVertecesCoords = 0;
	idVertecesUVs = 1;
	idVertecesNormals = 2;

	glUniform1i(idTextureSampler, 0); // The sampler will always be constant
}

void LiftTriShader::SetAmbientLight(const glm::vec3 & L)
{
	// I do not consider operations on the lights
}

void LiftTriShader::SetSceneLights(const std::vector<Light*>& Lights)
{
	// I do not consider operations on the lights
}

void LiftTriShader::SetMaterial(const Material * M)
{
	// Set the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, M->getTexture()->getIDTexture());
}

void LiftTriShader::SetCameraParameters(const glm::mat4 & ViewMatix, const glm::mat4 & ProjectionMatrix)
{
	matrixViewProject = ProjectionMatrix * ViewMatix;
}

void LiftTriShader::SetObjectParameters(const ActorParameters* P, const glm::mat4 & ModelMatrix)
{

	if(P == nullptr || static_cast<const LiftTriAP*>(P) == nullptr)
		glUniform1f(idDelta, 0.f);
	else
	{
		const LiftTriAP* p = (const LiftTriAP*)P;
		glUniform1f(idDelta, p->delta);
	}

	glm::mat4 mvp = matrixViewProject * ModelMatrix;
	glUniformMatrix4fv(idMatrix, 1, GL_FALSE, &mvp[0][0]);
}
