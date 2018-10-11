#pragma once

#include "Scene.hpp"

class CustomActorScene : public Scene
{
	Camera* camera;

	public:
		CustomActorScene();
		~CustomActorScene();

	protected:
		virtual void InizializeScene() override;
		virtual void UpdateScene(const UpdateParameters& SceneUpdateParameters) override;
};

