#pragma once

#include "Scene.hpp"

#include "BlackAndWhitePostProcessShader.hpp"
#include "BlurPostProcessShader.hpp"
#include "DepthPostProcessShader.hpp"

class PostProcessScene : public Scene
{
	Camera* camera = nullptr;

	BlackAndWhitePostProcessShader* blackAndWhite = nullptr;
	BlurPostProcessShader* postBlur = nullptr;
	DepthPostProcessShader* postDepth = nullptr;

	
	PostProcessEffect* currentEffect = nullptr; // Cutrrent selected effect

	public:
		PostProcessScene();
		~PostProcessScene();

	protected:
		virtual void InizializeScene() override;
		virtual void UpdateScene(const UpdateParameters& SceneUpdateParameters) override;

	private:
		void RemoveCurrentEffect();
};

