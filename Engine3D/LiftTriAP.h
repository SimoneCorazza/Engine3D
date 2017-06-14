#pragma once

#include "ActorParameters.h"

//Classe per i parametri da fornire allo shader da parte dell'attore
//per poter funzionare correttamente
class LiftTriAP : public ActorParameters
{
	public:
		float delta = 0; //Distanza dei poligoni

	public:
		LiftTriAP();
		~LiftTriAP();
};

