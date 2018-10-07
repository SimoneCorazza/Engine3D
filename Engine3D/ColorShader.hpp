#pragma once


#include "ModelShader.hpp"

// Shades for mono colored vertices
class ColorShader : public ModelShader
{
	GLuint idMatrix; // ID of the uniform variable of the array
	GLuint idColor; // ID of the uniform color variable to use

	// Partial matrix for the MVP (as the vertex shader takes the entire MVP matrix as input and not the individual matrices)
	glm::mat4 matrixViewProject;

	public:
		ColorShader();
		~ColorShader();

	// METHODS:
	public:

		virtual void LoadIDVar() override;

		virtual void SetAmbientLight(const glm::vec3& L) override;

		virtual void SetSceneLights(const std::vector<Light*>& Lights) override;

		virtual void SetMaterial(const Material* M) override;

		virtual void SetCameraParameters(const glm::mat4& ViewMatix, const glm::mat4& ProjectionMatrix) override;

		virtual void SetObjectParameters(const ActorParameters* P, const glm::mat4& ModelMatrix) override;
};
