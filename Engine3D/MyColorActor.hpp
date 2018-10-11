#pragma once

#include "Actor.hpp"

class MyColorActor : public Actor
{
	public:
		MyColorActor();
		~MyColorActor();

	public:
		void Update(const UpdateParameters& P) override;
};

