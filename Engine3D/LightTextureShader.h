#pragma once

#include "ModelShader.h"

//Shader che pertmette di renderizzare un modello con relativa texture
//e di applicare le luci della scena
class LightTextureShader : public ModelShader
{
	//Numero massimo di luci supportate dallo shader
	#define MAXIMUM_LIGTS 10

	struct LightUniformIDs
	{
		GLuint idPosition;
		GLuint idDiffuse;
		GLuint idSpecular;
		GLuint idConstantAttenuation, idLinearAttenuation, idQuadraticAttenuation;
		GLuint idSpotCutoff, idSpotExponent;
		GLuint idSpotDirection;
	};

	struct MaterialUniformIDs
	{
		GLuint idAmbient;
		GLuint idDiffuse;
		GLuint idSpecular;
		GLuint idShininess;
	};

	GLuint idM; //ID della matrice uniforme per il modello
	GLuint idV; //ID della matrice uniforme per la camera (View)
	GLuint idP; //ID della matrice uniforme per la proiezione
	GLuint idMTrans; //Id della matrice uniforme M trasposta
	GLuint idVInv; //Id della matrice della camera (View) inversa

	GLuint idTextureSampler;

	GLuint idAmbientLight; //Variabile uniforme per la luce d'ambiente
	LightUniformIDs lightsArrayComponetsID[MAXIMUM_LIGTS]; //Array contenente gli ID delle singole componenti dello struct dello shader
	MaterialUniformIDs materialUniformComponetID; //ID delle componenti uniformi dello shader per il materiale
	
	GLuint idLightsNumber; //ID della variabile nello shader indicante il numero di luci attualmente presenti nell'array

	public:
		LightTextureShader();
		~LightTextureShader();


	public:

		virtual void LoadIDVar() override;

		virtual void SetAmbientLight(const glm::vec3& L) override;

		virtual void SetSceneLights(const std::vector<Light*>& Lights) override;

		virtual void SetMaterial(const Material* M) override;

		virtual void SetCameraParameters(const glm::mat4& ViewMatix, const glm::mat4& ProjectionMatrix) override;

		virtual void SetObjectParameters(const ActorParameters* P, const glm::mat4& ModelMatrix) override;
};

