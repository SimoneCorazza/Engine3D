#include "StandardShader.hpp"

#include "Model.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "Texture2D.hpp"

// --- BUILDERS ---

StandardShader::StandardShader()
{
	idMatrix = 0;
	idTextureSampler = 0;
}

StandardShader::~StandardShader()
{
}



// --- METHODS ---


void StandardShader::LoadIDVar()
{
	idMatrix = GetVarID("MVP");
	idTextureSampler = GetVarID("textureSampler");

	idVertecesCoords = 0;
	idVertecesUVs = 1;

	glUniform1i(idTextureSampler, 0); // The sampler will always be constant
}

void StandardShader::SetAmbientLight(const glm::vec3 & L)
{
	// I do not consider operations on the lights
}

void StandardShader::SetSceneLights(const std::vector<Light*>& Lights)
{
	// I do not consider operations on the lights
}

void StandardShader::SetMaterial(const Material * M)
{
	// Set the texture
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
	glUniformMatrix4fv(idMatrix, 1, GL_FALSE, &mvp[0][0]); // Set the matrix
}