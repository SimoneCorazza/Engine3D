#pragma once

#include "Actor.hpp"

class MyLiftTriActor : public Actor
{
	public:
		MyLiftTriActor();
		~MyLiftTriActor();

	public:
		void Update(const UpdateParameters& P) override;
};

