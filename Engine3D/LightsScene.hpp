#pragma once

#include "Scene.hpp"

// Scene that uses ligths
class LightsScene : public Scene
{
	Camera* camera = nullptr;
	Actor* actor1 = nullptr;
	Actor* actor2 = nullptr;

	public:
		LightsScene();
		~LightsScene();

	protected:
		virtual void InizializeScene() override;
		virtual void UpdateScene(const UpdateParameters& SceneUpdateParameters) override;
};

