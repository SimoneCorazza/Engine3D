#pragma once

#include "ModelShader.hpp"

// Shader to render models by applying the texture as it is
class StandardShader : public ModelShader
{
	// ID OF THE SHADER VARIABLES:

	GLuint idMatrix;
	GLuint idTextureSampler;


	// Partial matrix for the MVP (as the vertex shader takes the entire MVP matrix as input and not the individual matrices)
	glm::mat4 matrixViewProject;

	// MANUFACTURERS:

	public:
		StandardShader();

		~StandardShader();

	// METHODS:
	public:

		virtual void LoadIDVar() override;

		virtual void SetAmbientLight(const glm::vec3& L) override;

		virtual void SetSceneLights(const std::vector<Light*>& Lights) override;

		virtual void SetMaterial(const Material* M) override;

		virtual void SetCameraParameters(const glm::mat4& ViewMatix, const glm::mat4& ProjectionMatrix) override;

		virtual void SetObjectParameters(const ActorParameters* P, const glm::mat4& ModelMatrix) override;

};

