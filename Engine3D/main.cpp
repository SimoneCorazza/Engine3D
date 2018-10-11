#include "Engine.hpp"

#include "StressTestScene.hpp"
#include "SimpleScene.hpp"
#include "ShadersWithParametersScene.hpp"
#include "CustomActorScene.hpp"
#include "LightsScene.hpp"
#include "PostProcessScene.hpp"

int main(int numArgs, char** args)
{
	Engine engine;
	engine.Inizialize();
	engine.CreateNewWindow("Engine3D", 640, 480);

	// --- DECOMMENT TO HAVE UNLIMITED FPS! ---
	// glfwSwapInterval (0);

	// --- CHOOSE A SCENE TO USE: ---
	Scene* scene = new SimpleScene();
	// Scene* scene = new StressTestScene();
	// Scene* scene = new ShadersWithParametersScene();
	// Scene* scene = new CustomActorScene();
	// Scene* scene = new LightsScene();
	// Scene* scene = new PostProcessScene();

	engine.StartGameLoop(scene);

    exit(EXIT_SUCCESS);
}