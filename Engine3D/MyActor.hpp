#pragma once

#include "Actor.hpp"

// Custom actor with custom logic
class MyActor : public Actor
{
	public:
		MyActor();
		~MyActor();

	public:
		void Update(const UpdateParameters& P) override;
};

