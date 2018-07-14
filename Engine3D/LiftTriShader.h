#pragma once

#include "ModelShader.h"

// Shader for models that allows you to move the triangles of the mesh
// NOTE: it does not work well with frustum culling
class LiftTriShader : public ModelShader
{
	// ID OF THE SHADER VARIABLES:

	GLuint idMatrix;
	GLuint idTextureSampler;
	GLuint idDelta;


	// Partial matrix for the MVP (as the vertex shader takes the entire MVP matrix as input and not the individual matrices)
	glm::mat4 matrixViewProject;


	// MANUFACTURERS:

	public:
		LiftTriShader();
		~LiftTriShader();


	// METHODS:
	public:

		virtual void LoadIDVar() override;

		virtual void SetAmbientLight(const glm::vec3& L) override;

		virtual void SetSceneLights(const std::vector<Light*>& Lights) override;

		virtual void SetMaterial(const Material* M) override;

		virtual void SetCameraParameters(const glm::mat4& ViewMatix, const glm::mat4& ProjectionMatrix) override;

		virtual void SetObjectParameters(const ActorParameters* P, const glm::mat4& ModelMatrix) override;
};

