#pragma once

#include "RenderingEngine.hpp"
#include "InputEngine.hpp"
#include "Scene.hpp"

struct GLFWwindow;

// Class that represents the engine
class Engine
{
	RenderingEngine renderingEngine;
	InputEngine inputEngine;
	InputState* lastInputState; // Last state of the input known

	GLFWwindow* window; // Window used by the engine
	Scene* actualScene; // Current scene to use
	bool gameLoop; // Indicates if true that the game loop will be executed

	public:
		Engine();
		~Engine();


	public:

		// It allows to initialize the engine
		void Inizialize();

		// --- WINDOWS ---


		// Create a window
		// @param [in] Title - Title of the window
		// @param [in] Width - Window length in pixels
		// @param [in] Height - Height of the window in pixels
		void CreateNewWindow(const char* Title, int Width, int Heigth);

		// Allows you to create a fullscreen window in the main monitor
		// @param [in] Title - Title of the window
		void CreateNewWindow(const char* Title);

		

		// --- GAME ---

		// Start the game loop
		// @param [in] Scene - Scene to use (no null)
		void StartGameLoop(Scene* Scene);

		// Allows to end the game cycle and finish the engine
		void EndGameLoop();

		// Set the scene to be rendered
		void setScene(Scene* Scene);

		// Gets the last known state of the input
		// NOTE: The pointer release is managed by this class
		InputState* getLastInputState();

		// @return Information on the work of the engine
		const RenderingEngineInfo& getRenderingEngineInfo() const;

	private:

		// Allows you to run the game loop
		void GameLoop();

		// Allows to release the resources allocated by the engine
		void Terminate();

		// It allows to take action when a new window has been created
		void CreatedNewWindow();
};

