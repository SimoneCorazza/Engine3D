#pragma once

#include "ModelShader.h"

//Shader per renderizzare dei modelli applicando la texture così com'è
class StandardShader : public ModelShader
{
	//ID DELLE VARIABILI DELLO SHADER:

	GLuint idMatrix;
	GLuint idTextureSampler;


	//Matrice parziale per il MVP (siccome il vertex shader prende in input l'intera matrice MVP e non le singole matrici)
	glm::mat4 matrixViewProject;

	//COSTRUTTORI:

	public:
		StandardShader();

		~StandardShader();

	//METODI:
	public:

		virtual void LoadIDVar() override;

		virtual void SetAmbientLight(const glm::vec3& L) override;

		virtual void SetSceneLights(const std::vector<Light*>& Lights) override;

		virtual void SetMaterial(const Material* M) override;

		virtual void SetCameraParameters(const glm::mat4& ViewMatix, const glm::mat4& ProjectionMatrix) override;

		virtual void SetObjectParameters(const ActorParameters* P, const glm::mat4& ModelMatrix) override;

};

