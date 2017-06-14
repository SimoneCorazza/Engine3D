#include "Engine.h"

#include "DEBUG.h"

#include <string>

#include <GL\glew.h> //Deve essere posizionata prima di "#include <GLFW\glfw3.h>"
#include <GLFW\glfw3.h>

#include "InputEngine.h"

#include "DEBUG.h"

#include <memory>

#include "Utility_FileSystem.h"


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


//Callback generato all'occorrere di un errore in GLFW
void GLFW_Error_Callback(int error, const char* description)
{
	ASSERT(false, (std::string("Error in GLFW (mediante callback): ") + std::string(description)).c_str()  );
}



void Engine::Inizialize()
{
	//Inizializzazione delle librerie:

	//GLFW
	if (!glfwInit())
	{
		RELEASE_CLOSE("Error in glfwInit()");
	}

	int m, i, r;
	glfwGetVersion(&m, &i, &r);
	LOG("GLFW version: %i.%i.%i", m, i, r);
	glfwSetErrorCallback(GLFW_Error_Callback); //Imposto il callback per gli errori di GLFW
}

void Engine::Terminate()
{
	//GLFW e finestre:
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
	//glfwWindowHint(GLFW_SAMPLES, 8);

	if (window) //Controllo per errori
		CreatedNewWindow();
	else
		RELEASE_CLOSE("Unable to create a new Window at: Engine::CreateNewWindow(const char*)");
}

void Engine::CreatedNewWindow()
{
	inputEngine.Inizialize(window);
	lastInputState = inputEngine.getInputState(); //Ottengo il primo stato dell'input engine, per l'nizializzazione delle classi
	glfwMakeContextCurrent(window);

	//Inizializzo GLEW
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
	
	//Inizializzo il rendering engine
	renderingEngine.Inizialize();
	renderingEngine.WindowResized(lastInputState->getWindowSize().x, lastInputState->getWindowSize().y); //Inizializzo anche la dimensione della finestra
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
	actualScene->Inizialize(this); //Inizializzo la scena
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

	//Variabili per quando la superficie della finestra diventa invalida:
	int glfwCursorMode;
	bool cursorReset = false;

	do
	{
		inputEngine.Update();
		delete lastInputState;
		lastInputState = inputEngine.getInputState();

		//Per tenere il conto che impiega per realizzare un ciclo
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
				renderingEngine.WindowResized(newS.x, newS.y); //Aggiorno il rendering engine (per aggiornare la grafica 2D)
				actualScene->OnScreenResize(newS.x, newS.y);
			}
			
			if (lastInputState->WindowSurfaceValid())
			{
				if (cursorReset) //Controllo se la dimensione della finestra è diventato valido
				{
					cursorReset = false;
					glfwSetInputMode(window, GLFW_CURSOR, glfwCursorMode); //Resetto il cursore come era prima
				}

				actualScene->Update(UpdateParameters(elapsed, lastInputState)); //Aggiorno la scena
				renderingEngine.RenderScene(*actualScene); //Renderizzo la scena
			}
			else if(!cursorReset) //Quando la finestra diventa invalida memorizzo lo stato del cursore e lo imposto come normale
			{
				cursorReset = true;
				glfwCursorMode = glfwGetInputMode(window, GLFW_CURSOR);
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
		}

		gameLoop &= glfwWindowShouldClose(window) == 0; //Controllo se la finestra deve chiudersi

		glfwSwapBuffers(window); //Scambio i fuffer mostrandolo sulla finestra
		glfwPollEvents(); //Gestisco la finestra

	} while (gameLoop);

	Terminate(); //Disalloco lo spazio allocato dall'engine
}
