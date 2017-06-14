#pragma once

#include <glm\glm.hpp>

#include "IE_CursorMode.h"
#include "Point2.h"

#include "InputEngine.h"

struct GLFWwindow;

//Classe che permette di accedere ai dispositivi di input e di modificarne lo stato
class InputState
{
	//Permetto all al gestore degli input di accedere totalmente alla classe
	friend class InputEngine;

	GLFWwindow* window; //Finestra di cui gestire l'input
	bool invalidated; //Se true ndica che this non può settare gli input

	//Struct che memorizza lo stato di un tasto generico
	struct KeyState
	{
		bool down; //Indica se il tasto nel frame precedente era su e adesso è giù
		bool up; //Indica se il tasto nel frame precedente era giu e adesso è su
		bool pressed; //Indica se il tasto è premuto
	};

	//--- KEYBOARD

	//Array sovradimensionato (siccome non tutte le celle sono usate)
	//che memorizzano lo stato dei tasti della tastiera
	//l'indice nell'array rappresenta l'ID di un tasto secondo GLFW
	KeyState* keyboard;

	//--- MOUSE

	Point2 cursor; //Posizione del cursore
	Point2 scrollWheel; //Stato della rotellina del mouse quando è stato preso questo stato
	Point2 delteScrollWheel; //Scroll della rotellina del mouse intercorse dallo stato precedente fino a questo
	KeyState* mouse; //Stato dei pulsanti del mouse
	IE_CursorMode cursorMode; //Modalità attuale del cursore

	//--- JOYSTICK

	public:

		//Classe che rappresenta uno stato di un Joystick
		class JoystickState
		{
			friend class InputState;

			KeyState* buttons; //Stato dei bottoni del joystick (la lunghezza dell'array varia da Joystick a Joystick)
			size_t countButt; //Numero di bottoni del joystick

			float* axes; //Stato degli assi del joystick
			size_t countAxes; //Numero di assi del joystick

			private:
				JoystickState();
			public:
				~JoystickState();

			public:

				//Indica se il bottone è stato alzato dallo stato precedente
				//@param[in] I - Indice base 0 che va ad identificare il bottone
				bool IsButtonUp(size_t I) const;

				//Indica se il bottone è stato premuto dallo stato precedente
				//@param[in] I - Indice base 0 che va ad identificare il bottone
				bool IsButtonDown(size_t I) const;

				//Indica se il bottone è premuto
				//@param[in] I - Indice base 0 che va ad identificare il bottone
				bool IsButtonPressed(size_t I) const;

				//Ottiene il numero di bottoni del joystick
				size_t getNumButtons() const;


				//Ottiene lo stato dell'asse indicato
				//@param[in] I - Indice di base 0 indicante l'asse del Joystick
				float getAxes(size_t I) const;

				//Ottiene il primo analogico del controller
				//@NOTA: se il joystick non ha abbastanza assi (almeno due) ritornerà (0, 0)
				glm::vec2 getFirstAnalog() const;

				//Ottiene il secondo analogico del controller
				//@NOTA: se il joystick non ha abbastanza assi (almeno quattro) ritornerà (0, 0)
				glm::vec2 getSecondAnalog() const;

				//Ottiene il numero di assi presenti nel joystick
				size_t getNumAxes() const;


			private:
				//Ottiene lo stato attuale di un'joystick
				//@param[in] GLFW_JoystickID - ID del Joystick secondo GLFW
				//@param[in] Prec - Stato precededente del Joystick (con il medesimo ID), null se non esiste uno stato precedente
				//@return Lo stato attuale del joystick; se l'ID indicato non è presente ritorna null
				//[Metodo creato per la classe friend InputState]
				static JoystickState* GetJoystickState(int GLFW_JoystickID, const JoystickState* Prec);
		};

	private:

		//Array per i joystick (array sovradimensionato)
		//l'indice dell'array rappresenta l'ID del Joystick assegnato da GLFW
		//assume valore null se non il joystick con id index non è presente
		JoystickState** joysticks;
		size_t connectedJoysticks; //Numero di Joysticks collegati


	//--- WINDOW

	Point2 windowSize; //Dimensione della finestra associata
	//Indica se la dimensione della finestra è stata cambiata dallo scorso frame (ma non se ha dimensione (0, 0))
	bool windowSizeChanged;
	bool windowSurfaceValid; //Idica se l'area della finestra è valida (l'area della superficie in pixel è > 0)


	private:
		InputState();
	public:
		~InputState();


	public:

		//---- FINESTRA DELL'APPLICAZIONE -----

		//Ottiene la dimensione  della finestra attule in pixel
		Point2 getWindowSize() const;

		//Ottiene un flag che indica se la finestra attualmente è ridotta ad icona (dimensione finestra (0, 0))
		//oppure semplicemente che la finestra ha dimensione non valida (es. è stata ridotta a tal punto da rendere una dimensione 0)
		bool WindowSurfaceValid() const;

		//Ottiene un flag che indica che la finestra di gioco è stata ridimensionata ma non se la dimensione 
		//della finestra è diventata nulla (area in pixel pari a 0)
		bool WindowResized() const;



		//---- TASTIERA -----

		//Ottiene un flag che indica se il tasto è stato rilasciato in questo stato
		//@param[in] GLFW_KeyCode - Tasto da controllare (ID relativo a GLFW)
		bool IsKeyUp(int GLFW_KeyCode) const;

		//Ottiene un flag che indica se il tasto è stato premuto in questo stato
		//@param[in] GLFW_KeyCode - Tasto da controllare (ID relativo a GLFW)
		bool IsKeyDown(int GLFW_KeyCode) const;

		//Ottiene un flag che indica se il tasto è stato attualmente premuto dall'utente
		//@param[in] GLFW_KeyCode - Tasto da controllare (ID relativo a GLFW)
		bool IsKeyPressed(int GLFW_KeyCode) const;

		//Ottiene l'insieme di caratteri premuti all'istante
		//@return Array di caratteri premuti; null in caso di nessun tasto carattere premuto
		//const char* GetPressedChar() const;


		//---- MOUSE ----

		//Ottiene un flag che indica se il bottone del mouse è stato rilasciato in questo stato
		//@param[in] GLFW_MouseButtonCode - Bottoen del mouse da controllare (ID relativo a GLFW)
		bool IsMouseButtonUp(int GLFW_MouseButtonCode) const;

		//Ottiene un flag che indica se il bottone del mouse è stato premuto in questo stato
		//@param[in] GLFW_MouseButtonCode - Bottoen del mouse da controllare (ID relativo a GLFW)
		bool IsMouseButtonDown(int GLFW_MouseButtonCode) const;

		//Ottiene un flag che indica se il bottone del mouse è stato attualmente premuto dall'utente
		//@param[in] GLFW_MouseButtonCode - Bottoen del mouse da controllare (ID relativo a GLFW)
		bool IsMouseButtonPressed(int GLFW_MouseButtonCode) const;

		//Ottiene la posizione del cursore nella finestra
		Point2 getCursorPosition() const;

		//Imposta la posizione del cursore relativa alla finestra attuale
		//@param[in] P - Posizione del cursore in pixel nella finestra
		void setCursorPosition(const Point2& P);

		//Imposta la posizione del cursore relativa alla finestra attuale
		//@param[in] X - Coordinata X della posizione in pixel del cursore nella finestra
		//@param[in] Y - Coordinata Y della posizione in pixel del cursore nella finestra
		//NOTA: L'opeazione può avere successo solo se this rappresenta l'ultimo stato dell'input
		void setCursorPosition(int x, int y);

		//Imposta la modalità in cui il cursore verrà trattato
		//NOTA: L'opeazione può avere successo solo se this rappresenta l'ultimo stato dell'input
		void setCursorMode(IE_CursorMode CursorMode);

		//Ottiene la modalità del cursore attualmente settata nell'engine
		IE_CursorMode getCursorMode() const;

		//Ottiene di quanto di è mossa la rotellina del mouse dallo scorso stato sull'asse X 
		//@return Intero che indica di quanto si è mossa la rotellina sull'asse X valore positivo se è verso sinista negativo se verso destra
		int getScrollWheelX() const;

		//Ottiene di quanto di è mossa la rotellina del mouse dallo scorso stato sull'asse Y
		//@return Intero che indica di quanto si è mossa la rotellina sull'asse X valore positivo se è verso l'alto negativo se verso il basso
		int getScrollWheelY() const;

		//Ottiene di quanto di è mossa la rotellina del mouse dallo scorso stato
		//@return Intero che indica di quanto si è mossa la rotellina
		Point2 getScrollWheel() const;

		//--- JOYSTICK ---

		//Ottiene il numero di joystick collegati
		size_t getNumConnectedJoystick() const;

		//Ottiene lo stato del Joystick indicato
		//@param[in] GLFW_JoystickID - ID secondo GLFW del Joystick
		//@return Stato del joystick o null se il Joystick con ID indicato non è presente
		//NOTA: Il rilascio del puntatore è gestoto da questa classe
		const JoystickState* getJoystickState(int GLFW_JoystickID) const;

		//Ottiene un'array con gli ID secondo GLFW dei Joysticks collegati
		//@return array contenente gli ID secondo GLFW dei Joysticks collegati, null se non ci sono joystik
		//NOTA: la gestione del puntatore restituito viene delegata all'utente
		//	(rilasciare la memoria con delete[])
		const int* getJoystickIDs() const;


	private:

		//Indica che this non è più l'ultimo stato più recente (ce ne è uno più recente)
		//e dunque a questa istanza viene privata la possibilità di modificare lo stato dell'input
		//[Creato per essere usato dalla classe friend InputEngine]
		void Invalidate();

		//Ottiene un oggetto InputState per lo stato dell'input attuale
		//@param[in] Window - Finestra da cui ottenere l'input
		//@param[in] PrecState - Stato precedente a questo, se non c'è passare null
		//[Creato per essere usato dalla classe friend InputEngine]
		static InputState* GetState(GLFWwindow* Window, const InputEngine* InputEngine, const InputState* PrecState);
};

