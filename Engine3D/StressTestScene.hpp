#pragma once

#include "Scene.hpp"
#include "TextBox.hpp"

// Scene for a stress test, to demonstrate 
class StressTestScene : public Scene
{
	Camera* camera;

	#define NUM_ACT_X 32
	#define NUM_ACT_Y 32
	#define NUM_ACT_Z 32

	Actor* actor[NUM_ACT_X][NUM_ACT_Y][NUM_ACT_Z];
	TextBox* txt = nullptr;

	public:
		StressTestScene();
		~StressTestScene();

	protected:
		virtual void InizializeScene() override;
		virtual void UpdateScene(const UpdateParameters& SceneUpdateParameters) override;
};

