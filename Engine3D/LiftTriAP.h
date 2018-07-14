#pragma once

#include "ActorParameters.h"

// Class for the parameters to be supplied to the shader by the actor
// in order to function properly
class LiftTriAP : public ActorParameters
{
	public:
		float delta = 0; // Polygon distance

	public:
		LiftTriAP();
		~LiftTriAP();
};

