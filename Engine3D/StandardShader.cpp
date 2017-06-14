#include "StandardShader.h"

#include "Model.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture2D.h"

//--- COSTRUTTORI ---

StandardShader::StandardShader()
{
	idMatrix = 0;
	idTextureSampler = 0;
}

StandardShader::~StandardShader()
{
}



//--- METODI ---


void StandardShader::LoadIDVar()
{
	idMatrix = GetVarID("MVP");
	idTextureSampler = GetVarID("textureSampler");

	idVertecesCoords = 0;
	idVertecesUVs = 1;

	glUniform1i(idTextureSampler, 0); //Il sampler sarà sempre costante
}

void StandardShader::SetAmbientLight(const glm::vec3 & L)
{
	//Non considero operazioni sulle luci
}

void StandardShader::SetSceneLights(const std::vector<Light*>& Lights)
{
	//Non considero operazioni sulle luci
}

void StandardShader::SetMaterial(const Material * M)
{
	//Imposto la texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, M->getTexture()->getIDTexture());
}

void StandardShader::SetCameraParameters(const glm::mat4 & ViewMatix, const glm::mat4 & ProjectionMatrix)
{
	matrixViewProject = ProjectionMatrix * ViewMatix;
}

void StandardShader::SetObjectParameters(const ActorParameters * P, const glm::mat4 & ModelMatrix)
{
	glm::mat4 mvp = matrixViewProject * ModelMatrix;
	glUniformMatrix4fv(idMatrix, 1, GL_FALSE, &mvp[0][0]); //Imposto la matrice
}