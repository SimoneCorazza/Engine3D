#pragma once

#include "Shader.hpp"


class Skybox;

// Shader to render a skybox
class SkyboxShader : public Shader
{
	GLuint idCubeSampler; // ID of the cube sampler
	GLuint idMatrix; // Id of the matrix

	public:
		SkyboxShader();
		~SkyboxShader();



	public:

		// Render the skybox
		// @param [in] S - Skybox to render
		// @param [in] CameraMatrix - Matrix representing the portion of skybox to display
		void RenderSkybox(const Skybox* S, const glm::mat4& CameraMatrix, const glm::vec3& CameraPos);

		virtual void LoadIDVar() override;
};

