#pragma once

#include <glm\glm.hpp>

class Camera;

//Classe che rappresenta una serie di parametri da passare al PostProcessShader
class PostProcessShaderParams
{
	glm::vec2 resolution;

	public:
		PostProcessShaderParams();

		~PostProcessShaderParams();

	public:

		//Imposta la risoluzione della porzione di video dove lo shader viene applicato
		void setResolution(const glm::vec2& R);
		//Ottiene la risoluzione della porzione di video dove lo shader viene applicato
		glm::vec2 getResolution() const;

		//Ottiene il tempo passato dall'avvio dell'applicazione in questo preciso istante
		static float getCurrentTime();
};

