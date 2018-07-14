#pragma once

#include "Actor.h"

// Custom actor class
class MyActor : public Actor
{
	public:
		MyActor();
		~MyActor();

	public:
		void Update(const UpdateParameters& P) override;
};

