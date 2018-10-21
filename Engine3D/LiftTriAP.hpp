#pragma once

#include "ActorParameters.hpp"

// Class for the ActorParameters for the LiftTri
class LiftTriAP : public ActorParameters
{
	public:
		// Maximum vertex distance
		float delta = 0;

	public:
		LiftTriAP();
		~LiftTriAP();
};

