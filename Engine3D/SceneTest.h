#pragma once

#include "Scene.h"

// Scene created as a test for the engine
class SceneTest : public Scene
{
	Camera* camera;

	public:
		SceneTest();
		~SceneTest();

	public:

	protected:

		virtual void InizializeScene() override;

		virtual void UpdateScene(const UpdateParameters& SceneUpdateParameters) override;
};

