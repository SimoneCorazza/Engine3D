#pragma once

#include "Shader.hpp"


class Skybox;

// Shader to render a skybox
class SkyboxShader : public Shader
{
	// ID of the cube sampler
	GLuint idCubeSampler;

	// Id of the matrix
	GLuint idMatrix;

	public:
		SkyboxShader();
		~SkyboxShader();



	public:

		// Render the skybox
		// @param[in] S - Skybox to render
		// @param[in] CameraMatrix - Matrix representing the portion of skybox to display
		void RenderSkybox(const Skybox* S, const glm::mat4& CameraMatrix, const glm::vec3& CameraPos);

		virtual void LoadIDVar() override;
};

