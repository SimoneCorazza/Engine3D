#pragma once

#include "Scene.hpp"

// Scene with basic content
class SimpleScene : public Scene
{
	Camera* camera;

public:
	SimpleScene();
	~SimpleScene();

protected:
	virtual void InizializeScene() override;
	virtual void UpdateScene(const UpdateParameters& SceneUpdateParameters) override;
};
