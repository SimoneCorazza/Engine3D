#pragma once

#include "RenderingEngine.h"
#include "InputEngine.h"
#include "Scene.h"

struct GLFWwindow;

//Classe che rappresenta l'engine
class Engine
{
	RenderingEngine renderingEngine;
	InputEngine inputEngine;
	InputState* lastInputState; //Ultimo stato dell'input conoscuto

	GLFWwindow* window; //Finestra utilizzata dall'engine
	Scene* actualScene; //Scena attuale da utilizzare
	bool gameLoop; //Indica se true che il game loop verrà eseguito

	public:
		Engine();
		~Engine();


	public:

		//Permette di inizializzare l'engine
		void Inizialize();

		//--- FINESTRE ---


		//Consente di creare una finestra
		//@param[in] Title - Titolo della finestra
		//@param[in] Width - Lunghezza della finestra in pixel
		//@param[in] Heigth - Altezza della finestra in pixel
		void CreateNewWindow(const char* Title, int Width, int Heigth);

		//Consente di creare una finestra in fullscreen nel monitor principale
		//@param[in] Title - Titolo della finestra
		void CreateNewWindow(const char* Title);

		

		//--- GAME ---

		//Consente di iniziare il game loop
		//@param[in] Scene - Scena da utilizzare (no null)
		void StartGameLoop(Scene* Scene);

		//Permette di terminare il ciclo di gioco e terminare l'engine
		void EndGameLoop();

		//Setta la scena da renderizzare
		void setScene(Scene* Scene);

		//Ottiene l'ultimo stato conoscuto dell'input
		//NOTA: Il rilascio del puntatore è gestito da questa classe
		InputState* getLastInputState();

		//@return Informazionu sull'operato dell'engine
		const RenderingEngineInfo& getRenderingEngineInfo() const;

	private:

		//Consente di eseguire il game loop
		void GameLoop();

		//Permette di rilasciare le risorse allocate dall'engine
		void Terminate();

		//Permette di prendere provvedimenti quando una nuova finestra è stata creata
		void CreatedNewWindow();
};

