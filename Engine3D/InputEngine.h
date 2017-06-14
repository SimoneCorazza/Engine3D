#pragma once

#include  "Point2.h";
struct GLFWwindow;
class InputState;

//Classe che permette di gestire gli input dell'utente nell'applicazione
//questa classe è concepita per essere eseguita periodicamente, aggiornado lo stato dell'input
class InputEngine
{

	/*
	Invariante degli attributi della classe: essi non vengono aggiornati se non in un Update salvo alcune eccezioni
	NOTA: alcune variabili possono essere settate dall'esterno (es. la posizione del cursore) e queste vanno modificato
	istantaneamente (altrimenti BUG es. per il cursore: la posizione del cursore viene settato e subito dopo letta la sua posizione per lo stato)
	*/

	GLFWwindow* window; //Finestra da cui ricavare l'input

	InputState* inputState; //Stato dell'input attuale
	Point2 scrollWheel; //Stato della rotellina del mouse

	public:

		InputEngine();
		~InputEngine();

	public:

		//Permette di inizializzare l'engine degli input
		//@param[in] Window - Finestra di cui si vuole ottenere l'input
		void Inizialize(GLFWwindow* Window);

		//Permette di aggiornare lo stato della calasse eseguendo un'update dello stato dell'input
		void Update();

		//Ottiene lo stato dell'input per questo frame
		//NOTA: la gestione del puntatore è affidata all'utente
		InputState* getInputState();

		//--- SCROLL WHEEL ----

		//Ottiene lo stato della rotellina del mouse a partire dall'istanzazione della classe
		//@return Stato della rotella del mouse con movimento sull'asse X e Y della rotellina
		Point2 getScroolWheelState() const;

		//--- DEFAULT WINDOWS BOX ---

		enum MessageBox_Return
		{
			MB_RETURN_Abort,
			MB_RETURN_Cancel,
			MB_RETURN_Continue,
			MB_RETURN_Ingnore,
			MB_RETURN_No,
			MB_RETURN_OK,
			MB_RETURN_Retry,
			MB_RETURN_TryAgain,
			MB_RETURN_Yes,
		};

		enum MessageBox_Buttons
		{
			MB_BTN_AbortRetryIgnore,
			MB_BTN_CancelTryAgainContinue,
			MB_BTN_Help,
			MB_BTN_OK,
			MB_BTN_OKCancel,
			MB_BTN_RetryCancel,
			MB_BTN_YesNo,
			MB_BTN_YesNoCancel
		};

		enum MessageBox_Icons
		{
			MB_ICON_Exclamation,
			MB_ICON_Warning,
			MB_ICON_Information,
			MB_ICON_Asterisk,
			MB_ICON_Question,
			MB_ICON_Stop,
			MB_ICON_Error,
			MB_ICON_Hand,
			MB_ICON_None,
		};

		enum MessageBox_DefaultButton
		{
			MB_DEFAULTBUTTON_1,
			MB_DEFAULTBUTTON_2,
			MB_DEFAULTBUTTON_3,
			MB_DEFAULTBUTTON_4,
		};

		//Mostra una message box con il tasto OK
		//@param[in] Title - Titolo sulla barra della finestra della message box
		//@param[in] Text - Testo della message box
		static void MessageBoxShow(const char* Title, const char* Text);

		//Mostra una message box
		//@param[in] Title - Titolo sulla barra della finestra della message box
		//@param[in] Text - Testo della message box
		//@param[in] Buttons - Bottoni presenti nella box
		//@return Bottone cliccato dall'utente
		static MessageBox_Return MessageBoxShow(const char* Title, const char* Text, MessageBox_Buttons Buttons);

		//Mostra una message box
		//@param[in] Title - Titolo sulla barra della finestra della message box
		//@param[in] Text - Testo della message box
		//@param[in] Buttons - Bottoni presenti nella box
		//@param[in] DefaultBtn - Bottone selezionato di default
		//@return Bottone cliccato dall'utente
		static MessageBox_Return MessageBoxShow(const char* Title, const char* Text, MessageBox_Buttons Buttons, MessageBox_DefaultButton DefaultBtn);

		//Mostra una message box
		//@param[in] Title - Titolo sulla barra della finestra della message box
		//@param[in] Text - Testo della message box
		//@param[in] Buttons - Bottoni presenti nella box
		//@param[in] Icon - Icona da mostrare
		//@return Bottone cliccato dall'utente
		static MessageBox_Return MessageBoxShow(const char* Title, const char* Text, MessageBox_Buttons Buttons, MessageBox_Icons Icon);

		//Mostra una message box
		//@param[in] Title - Titolo sulla barra della finestra della message box
		//@param[in] Text - Testo della message box
		//@param[in] Buttons - Bottoni presenti nella box
		//@param[in] DefaultBtn - Bottone selezionato di default
		//@param[in] Icon - Icona da mostrare
		//@return Bottone cliccato dall'utente
		static MessageBox_Return MessageBoxShow(const char* Title, const char* Text, MessageBox_Buttons Buttons, MessageBox_DefaultButton DefaultBtn, MessageBox_Icons Icon);
};