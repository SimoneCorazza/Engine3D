#pragma once

#include "Shader.h"


class Skybox;

//Shader per renderizzare uno skybox
class SkyboxShader : public Shader
{
	GLuint idCubeSampler; //ID del cube sampler
	GLuint idMatrix; //Id della matrice

	public:
		SkyboxShader();
		~SkyboxShader();



	public:

		//Renderizza lo skybox
		//@param[in] S - Skybox da renderizzare
		//@param[in] CameraMatrix - Matrice che rappresenta la porzione di skybox da visualizzare
		void RenderSkybox(const Skybox* S, const glm::mat4& CameraMatrix, const glm::vec3& CameraPos);

		virtual void LoadIDVar() override;
};

