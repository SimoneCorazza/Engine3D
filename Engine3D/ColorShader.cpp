#include "ColorShader.hpp"

#include "DEBUG.hpp"
#include "ColorShaderAP.hpp"

ColorShader::ColorShader()
{
	idMatrix = 0;
	idColor = 0;
}

ColorShader::~ColorShader()
{
}

void ColorShader::LoadIDVar()
{
	idMatrix = GetVarID("MVP");
	idColor = GetVarID("color");

	idVertecesCoords = 0;
}

void ColorShader::SetAmbientLight(const glm::vec3 & L)
{
	// I do not consider the lights in this shader
}

void ColorShader::SetSceneLights(const std::vector<Light*>& Lights)
{
	// I do not consider the lights in this shader
}

void ColorShader::SetMaterial(const Material * M)
{
	// I do not consider the material in this shader
}

void ColorShader::SetCameraParameters(const glm::mat4 & ViewMatix, const glm::mat4 & ProjectionMatrix)
{
	matrixViewProject = ProjectionMatrix * ViewMatix;
}

void ColorShader::SetObjectParameters(const ActorParameters* P, const glm::mat4& ModelMatrix)
{
	const ColorShaderAP* params = dynamic_cast<const ColorShaderAP*>(P);
	if (P == nullptr || params == nullptr)
		glUniform4f(idColor, 0, 0, 0, 1);
	else
	{
		glUniform4f(idColor, params->color.r, params->color.g, params->color.b, 
			params->color.a);
	}

	glm::mat4 mvp = matrixViewProject * ModelMatrix;
	glUniformMatrix4fv(idMatrix, 1, GL_FALSE, &mvp[0][0]); // Set the matrix
}