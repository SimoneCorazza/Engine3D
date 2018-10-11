#pragma once

#include "Scene.hpp"

// Scene that uses shaders with customizable parameters passed by the actors
class ShadersWithParametersScene : public Scene
{
	Camera* camera;

	public:
		ShadersWithParametersScene();
		~ShadersWithParametersScene();

	protected:
		virtual void InizializeScene() override;
		virtual void UpdateScene(const UpdateParameters& SceneUpdateParameters) override;
};

