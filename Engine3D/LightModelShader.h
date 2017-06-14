#pragma once

#include "ModelShader.h"

//Classe astratta che permette di rappresentare uno shader utilizzato
//per renderizzare un modello con effetti di luce
class LightModelShader : public ModelShader
{
	public:
		LightModelShader();
		~LightModelShader();

	public:

		//Imposta la luce dell'ambiente da applicare al modello
		//(luce minima che possiederà l'ogetto)
		virtual void setAmbientLight(glm::vec3 AbientLight) const abstract;


};

