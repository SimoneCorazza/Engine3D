#pragma once

#include  "Point2.h";
struct GLFWwindow;
class InputState;

// Class that allows you to manage user input in the application
// this class is designed to run periodically, updating the status of the input
class InputEngine
{

	/*
	Invariant of the class attributes: they are not updated except in an Update with some exceptions
	NOTE: some variables can be set from outside (eg the cursor position) and these must be changed
	instantaneously (otherwise BUG eg for the cursor: the cursor position is set and immediately after reading its position for the status)
	*/

	GLFWwindow* window; // Window from which to obtain the input

	InputState* inputState; // Status of current input
	Point2 scrollWheel; // Mouse wheel status

	public:

		InputEngine();
		~InputEngine();

	public:

		// It allows to initialize the input engine
		// @param [in] Window - Window whose input is to be obtained
		void Inizialize(GLFWwindow* Window);

		// It allows to update the status of the cabinet by performing an update of the input status
		void Update();

		// Gets the status of the input for this frame
		// NOTE: the pointer is managed by the user
		InputState* getInputState();

		// --- SCROLL WHEEL ----

		// Gets the status of the mouse wheel starting from the class's instance
		// @return Status of the mouse wheel with movement on the X and Y axis of the wheel
		Point2 getScroolWheelState() const;

		// --- DEFAULT WINDOWS BOX ---

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

		// Show a message box with the OK button
		// @param [in] Title - Title on the message box window bar
		// @param [in] Text - Text of the message box
		static void MessageBoxShow(const char* Title, const char* Text);

		// Show a message box
		// @param [in] Title - Title on the message box window bar
		// @param [in] Text - Text of the message box
		// @param [in] Buttons - Buttons in the box
		// @return Button clicked by the user
		static MessageBox_Return MessageBoxShow(const char* Title, const char* Text, MessageBox_Buttons Buttons);

		// Show a message box
		// @param [in] Title - Title on the message box window bar
		// @param [in] Text - Text of the message box
		// @param [in] Buttons - Buttons in the box
		// @param [in] DefaultBtn - Button selected by default
		// @return Button clicked by the user
		static MessageBox_Return MessageBoxShow(const char* Title, const char* Text, MessageBox_Buttons Buttons, MessageBox_DefaultButton DefaultBtn);

		// Show a message box
		// @param [in] Title - Title on the message box window bar
		// @param [in] Text - Text of the message box
		// @param [in] Buttons - Buttons in the box
		// @param [in] Icon - Icon to show
		// @return Button clicked by the user
		static MessageBox_Return MessageBoxShow(const char* Title, const char* Text, MessageBox_Buttons Buttons, MessageBox_Icons Icon);

		// Show a message box
		// @param [in] Title - Title on the message box window bar
		// @param [in] Text - Text of the message box
		// @param [in] Buttons - Buttons in the box
		// @param [in] DefaultBtn - Button selected by default
		// @param [in] Icon - Icon to show
		// @return Button clicked by the user
		static MessageBox_Return MessageBoxShow(const char* Title, const char* Text, MessageBox_Buttons Buttons, MessageBox_DefaultButton DefaultBtn, MessageBox_Icons Icon);
};