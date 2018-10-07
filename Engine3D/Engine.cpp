#include "Engine.hpp"

#include "DEBUG.hpp"

#include <string>

#include <GL\glew.h> // It must be placed before "#include <GLFW \ glfw3.h>"
#include <GLFW\glfw3.h>

#include "InputEngine.hpp"

#include "DEBUG.hpp"

#include <memory>

#include "Utility_FileSystem.hpp"


Engine::Engine()
{
	actualScene = nullptr;
	window = nullptr;
	lastInputState = nullptr;
	gameLoop = false;
}


Engine::~Engine()
{
}


// Callback generated when an error occurs in GLFW
void GLFW_Error_Callback(int error, const char* description)
{
	ASSERT(false, (std::string("Error in GLFW (mediante callback): ") + std::string(description)).c_str()  );
}



void Engine::Inizialize()
{
	// Initialization of libraries:

	// GLFW
	if (!glfwInit())
	{
		RELEASE_CLOSE("Error in glfwInit()");
	}

	int m, i, r;
	glfwGetVersion(&m, &i, &r);
	LOG("GLFW version: %i.%i.%i", m, i, r);
	glfwSetErrorCallback(GLFW_Error_Callback); // Set the callback for GLFW errors
}

void Engine::Terminate()
{
	// GLFW and windows:
	glfwDestroyWindow(window);
	glfwTerminate();
}






void Engine::CreateNewWindow(const char* Title, int Width, int Heigth)
{
	window = glfwCreateWindow(Width, Heigth, Title, nullptr, nullptr);
	if (window)
		CreatedNewWindow();
	else
		RELEASE_CLOSE("Unable to create a new Window at: Engine::CreateNewWindow(const char*, int, int)");
}

void Engine::CreateNewWindow(const char* Title)
{
	GLFWmonitor* m = glfwGetPrimaryMonitor();
	const GLFWvidmode* v = glfwGetVideoMode(m);
	window = glfwCreateWindow(v->width, v->height, Title, m, nullptr);
	// glfwWindowHint (GLFW_SAMPLES, 8);

	if (window) // Checking for errors
		CreatedNewWindow();
	else
		RELEASE_CLOSE("Unable to create a new Window at: Engine::CreateNewWindow(const char*)");
}

void Engine::CreatedNewWindow()
{
	inputEngine.Inizialize(window);
	lastInputState = inputEngine.getInputState(); // I get the first status of the input engine, for the initialization of classes
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		RELEASE_CLOSE((std::string("Error: ") + std::string((const char*)glewGetErrorString(err))).c_str());
	}

	LOG("Created new window:\n"
		"	GLEW version: %s\n"
		"	OpenGL version: %s\n"
		"	Venditor string: %s\n"
		"	Renderer: %s\n",
		glewGetString(GLEW_VERSION),
		glGetString(GL_VERSION),
		glGetString(GL_VENDOR),
		glGetString(GL_RENDERER)
		);
	
	// Initialize the rendering engine
	renderingEngine.Inizialize();
	renderingEngine.WindowResized(lastInputState->getWindowSize().x, lastInputState->getWindowSize().y); // I also initialize the window size
}

void Engine::StartGameLoop(Scene* Scene)
{
	setScene(Scene);
	gameLoop = true;
	GameLoop();
}

void Engine::EndGameLoop()
{
	gameLoop = false;
}

void Engine::setScene(Scene* Scene)
{
	actualScene = Scene;
	actualScene->Inizialize(this); // Initialize the scene
}

InputState * Engine::getLastInputState()
{
	return lastInputState;
}

const RenderingEngineInfo& Engine::getRenderingEngineInfo() const
{
	return renderingEngine.getRenderingEngineInfo();
}

void Engine::GameLoop()
{
	bool end = false;
	double last = glfwGetTime();

	// Variables for when the window surface becomes invalid:
	int glfwCursorMode;
	bool cursorReset = false;

	do
	{
		inputEngine.Update();
		delete lastInputState;
		lastInputState = inputEngine.getInputState();

		// To keep the bill it takes to make a cycle
		double current = glfwGetTime();
		float elapsed = float(current - last);
		last = current;

		if (actualScene == nullptr)
			LOG("No scene to update or render: Engine::GameLoop()");
		else
		{
			if (lastInputState->WindowResized())
			{
				Point2 newS = lastInputState->getWindowSize();
				renderingEngine.WindowResized(newS.x, newS.y); // Update rendering engine (to update 2D graphics)
				actualScene->OnScreenResize(newS.x, newS.y);
			}
			
			if (lastInputState->WindowSurfaceValid())
			{
				if (cursorReset) // Check if the window size has become valid
				{
					cursorReset = false;
					glfwSetInputMode(window, GLFW_CURSOR, glfwCursorMode); // I reset the cursor as it was before
				}

				actualScene->Update(UpdateParameters(elapsed, lastInputState)); // I update the scene
				renderingEngine.RenderScene(*actualScene); // I render the scene
			}
			else if(!cursorReset) // When the window becomes invalid, I memorize the state of the cursor and set it as normal
			{
				cursorReset = true;
				glfwCursorMode = glfwGetInputMode(window, GLFW_CURSOR);
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
		}

		gameLoop &= glfwWindowShouldClose(window) == 0; // Check if the window has to close

		glfwSwapBuffers(window); // Exchange the fuffer by showing it on the window
		glfwPollEvents(); // I manage the window

	} while (gameLoop);

	Terminate(); // Disallocate the space allocated by the engine
}
