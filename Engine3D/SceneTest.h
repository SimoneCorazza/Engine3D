#pragma once

#include "Scene.h"

//Scena creata come test per l'engine
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

