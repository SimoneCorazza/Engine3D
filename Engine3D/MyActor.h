#pragma once

#include "Actor.h"

//Classe attore personalizzata
class MyActor : public Actor
{
	public:
		MyActor();
		~MyActor();

	public:
		void Update(const UpdateParameters& P) override;
};

