#include "LightTextureShader.h"

#include <glm\gtc\matrix_inverse.hpp>
#include <string>

#include "Model.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture2D.h"
#include "Actor.h"

LightTextureShader::LightTextureShader()
{
	
}


LightTextureShader::~LightTextureShader()
{
}




void LightTextureShader::LoadIDVar()
{
	idVertecesCoords = 0;
	idVertecesUVs = 1;
	idVertecesNormals = 2;
	idM = GetVarID("m");
	idV = GetVarID("v");
	idP = GetVarID("p");
	idMTrans = GetVarID("m_3x3_inv_transp");
	idVInv = GetVarID("v_inv");

	idTextureSampler = GetVarID("texture");

	idAmbientLight = GetVarID("scene_ambient");
	idLightsNumber = GetVarID("lightsNumber");

	materialUniformComponetID.idAmbient = GetVarID("frontMaterial.ambient");
	materialUniformComponetID.idDiffuse = GetVarID("frontMaterial.diffuse");
	materialUniformComponetID.idSpecular = GetVarID("frontMaterial.specular");
	materialUniformComponetID.idShininess = GetVarID("frontMaterial.shininess");

	for (int i = 0; i < MAXIMUM_LIGTS; i++)
	{
		// First part always the same for the following operations examples:
		// "lights [0].", "lights [1].", "lights [2].", ...
		std::string first = std::string("lights[") + std::to_string(i) + std::string("].");

		lightsArrayComponetsID[i].idPosition = GetVarID(first + std::string("position"));
		lightsArrayComponetsID[i].idDiffuse = GetVarID(first + std::string("diffuse"));
		lightsArrayComponetsID[i].idSpecular = GetVarID(first + std::string("specular"));
		lightsArrayComponetsID[i].idConstantAttenuation = GetVarID(first + std::string("constantAttenuation"));
		lightsArrayComponetsID[i].idLinearAttenuation = GetVarID(first + std::string("linearAttenuation"));
		lightsArrayComponetsID[i].idQuadraticAttenuation = GetVarID(first + std::string("quadraticAttenuation"));
		lightsArrayComponetsID[i].idSpotCutoff = GetVarID(first + std::string("spotCutoff"));
		lightsArrayComponetsID[i].idSpotExponent = GetVarID(first + std::string("spotExponent"));
		lightsArrayComponetsID[i].idSpotDirection = GetVarID(first + std::string("spotDirection"));
	}

	glUniform1i(idTextureSampler, 0); // I leave the texture used at zero (it will always be constant)
}

void LightTextureShader::SetAmbientLight(const glm::vec3 & L)
{
	// The w must always be 1 (transparency not possible)
	glUniform4f(idAmbientLight, L.x, L.y, L.z, 1.0f);
}

// const Model * lastRenderedModel = nullptr; // Last rendered model

void LightTextureShader::SetSceneLights(const std::vector<Light*>& Lights)
{
	// lastRenderedModel = nullptr;

	glUniform1i(idLightsNumber, (int)Lights.size()); // Set the number of lights to be set

	// I set the various parameters for each field of light:
	for (int i = 0; i < Lights.size() && i < MAXIMUM_LIGTS; i++)
	{
		Light* l = Lights[i];
		glUniform4fv(lightsArrayComponetsID[i].idPosition, 1, &l->position[0]);
		glUniform4fv(lightsArrayComponetsID[i].idDiffuse, 1, &l->diffuse[0]);
		glUniform4fv(lightsArrayComponetsID[i].idSpecular, 1, &l->specular[0]);
		glUniform1f(lightsArrayComponetsID[i].idConstantAttenuation, l->constantAttenuation);
		glUniform1f(lightsArrayComponetsID[i].idLinearAttenuation, l->linearAttenuation);
		glUniform1f(lightsArrayComponetsID[i].idQuadraticAttenuation, l->quadraticAttenuation);
		glUniform1f(lightsArrayComponetsID[i].idSpotCutoff, l->spotCutoff);
		glUniform1f(lightsArrayComponetsID[i].idSpotExponent, l->spotExponent);
		glUniform3fv(lightsArrayComponetsID[i].idSpotDirection, 1, &l->spotDirection[0]);
	}
}

void LightTextureShader::SetMaterial(const Material * M)
{
	// Imposed the material:
	glUniform4f(materialUniformComponetID.idAmbient, M->getAmbient().x, M->getAmbient().y, M->getAmbient().z, 1.0f);
	glUniform4f(materialUniformComponetID.idDiffuse, M->getDiffuse().x, M->getDiffuse().y, M->getDiffuse().z, 1.0f);
	glUniform4f(materialUniformComponetID.idSpecular, M->getSpecular().x, M->getSpecular().y, M->getSpecular().z, 1.0f);
	glUniform1f(materialUniformComponetID.idShininess, M->getShininess());

	// I leave the texture:
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, M->getTexture()->getIDTexture());
}

void LightTextureShader::SetCameraParameters(const glm::mat4 & ViewMatix, const glm::mat4 & ProjectionMatrix)
{
	glUniformMatrix4fv(idV, 1, GL_FALSE, &ViewMatix[0][0]);
	glUniformMatrix4fv(idP, 1, GL_FALSE, &ProjectionMatrix[0][0]);
	glm::mat4 v_inv = glm::inverse(ViewMatix);
	glUniformMatrix4fv(idVInv, 1, GL_FALSE, &v_inv[0][0]);
}



void LightTextureShader::SetObjectParameters(const ActorParameters* P, const glm::mat4& ModelMatrix)
{
	// P is accepting NULL in this shader

	glm::mat4 m = ModelMatrix;
	glm::mat3 m_3x3_inv_transp = glm::transpose(glm::inverse(glm::mat3(ModelMatrix)));

	// Set the matrices:
	glUniformMatrix4fv(idM, 1, GL_FALSE, &m[0][0]);
	glUniformMatrix3fv(idMTrans, 1, GL_FALSE, &m_3x3_inv_transp[0][0]);
}
