#pragma once

#include "ModelShader.h"

//Shader per modelli che permette di spostare i triangoli della mesh
//NOTA: non funziona bene con il frustum culling
class LiftTriShader : public ModelShader
{
	//ID DELLE VARIABILI DELLO SHADER:

	GLuint idMatrix;
	GLuint idTextureSampler;
	GLuint idDelta;


	//Matrice parziale per il MVP (siccome il vertex shader prende in input l'intera matrice MVP e non le singole matrici)
	glm::mat4 matrixViewProject;


	//COSTRUTTORI:

	public:
		LiftTriShader();
		~LiftTriShader();


	//METODI:
	public:

		virtual void LoadIDVar() override;

		virtual void SetAmbientLight(const glm::vec3& L) override;

		virtual void SetSceneLights(const std::vector<Light*>& Lights) override;

		virtual void SetMaterial(const Material* M) override;

		virtual void SetCameraParameters(const glm::mat4& ViewMatix, const glm::mat4& ProjectionMatrix) override;

		virtual void SetObjectParameters(const ActorParameters* P, const glm::mat4& ModelMatrix) override;
};

