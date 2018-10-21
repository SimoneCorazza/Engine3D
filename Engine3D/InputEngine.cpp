#include "InputEngine.hpp"

#include "DEBUG.hpp"
#include <GLFW\glfw3.h>
#include "Point2.hpp"
#include "IE_CursorMode.hpp"
#include "InputState.hpp"

#ifdef WINDOWS
#include <Windows.h>
#else
#error Unknown OS library
#endif


InputEngine::InputEngine()
{
	window = nullptr;
	inputState = nullptr;
}

InputEngine::~InputEngine()
{
	
}

Point2 sW;
void ScrollWheel_Callback(GLFWwindow * w, double x, double y)
{
	sW.x += (int)x;
	sW.y += (int)y;
}


void InputEngine::Inizialize(GLFWwindow * Window)
{
	ASSERT(Window != nullptr, "Argument null not acepted in InputEngine::Inizialize()");

	window = Window;
	inputState = InputState::GetState(Window, this, nullptr);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GL_FALSE);

	glfwSetScrollCallback(window, ScrollWheel_Callback);
}

void InputEngine::Update()
{
	// Check that the key mode of the user has not changed
	ASSERT(glfwGetInputMode(window, GLFW_STICKY_KEYS) != GL_TRUE, "GLFW_STICKY_KEYS is True -> for the correct function of the class it must be false");
	ASSERT(glfwGetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS) != GL_TRUE, "GLFW_STICKY_MOUSE_BUTTONS is True -> for the correct function of the class it must be false");

	scrollWheel = sW; // I update the scroll wheel

	if (inputState != nullptr) // Invalidate the instance of the previous InputState
		inputState->Invalidate();

	inputState = InputState::GetState(window, this, inputState);
}

InputState* InputEngine::getInputState()
{
	return inputState;
}

Point2 InputEngine::getScroolWheelState() const
{
	return scrollWheel;
}


void InputEngine::MessageBoxShow(const char * Title, const char * Text)
{
	MessageBoxShow(Title, Text, MB_BTN_OK);
}

InputEngine::MessageBox_Return InputEngine::MessageBoxShow(const char* Title, const char* Text, MessageBox_Buttons Buttons)
{
	return MessageBoxShow(Title, Text, Buttons, MB_DEFAULTBUTTON_1);
}

InputEngine::MessageBox_Return InputEngine::MessageBoxShow(const char * Title, const char * Text, MessageBox_Buttons Buttons, MessageBox_DefaultButton DefaultBtn)
{
	return MessageBoxShow(Title, Text, Buttons, DefaultBtn, MB_ICON_None);
}

InputEngine::MessageBox_Return InputEngine::MessageBoxShow(const char * Title, const char * Text, MessageBox_Buttons Buttons, MessageBox_Icons Icon)
{
	return MessageBoxShow(Title, Text, Buttons, MB_DEFAULTBUTTON_1, Icon);
}

InputEngine::MessageBox_Return InputEngine::MessageBoxShow(const char * Title, const char * Text, MessageBox_Buttons Buttons, MessageBox_DefaultButton DefaultBtn, MessageBox_Icons Icon)
{
#ifdef WINDOWS

	// Windows
	// Complite explenation at https://msdn.microsoft.com/en-us/library/windows/desktop/ms645505(v=vs.85).aspx

	UINT options = 0;

	switch (Buttons)
	{
	case InputEngine::MB_BTN_AbortRetryIgnore: options |= MB_ABORTRETRYIGNORE;
		break;
	case InputEngine::MB_BTN_CancelTryAgainContinue: options |= MB_CANCELTRYCONTINUE;
		break;
	case InputEngine::MB_BTN_Help: options |= MB_HELP;
		break;
	case InputEngine::MB_BTN_OK: options |= MB_OK;
		break;
	case InputEngine::MB_BTN_OKCancel: options |= MB_OKCANCEL;
		break;
	case InputEngine::MB_BTN_RetryCancel: options |= MB_RETRYCANCEL;
		break;
	case InputEngine::MB_BTN_YesNo: options |= MB_YESNO;
		break;
	case InputEngine::MB_BTN_YesNoCancel: options |= MB_YESNOCANCEL;
		break;

	default:
		break;
	}

	switch (Icon)
	{
	case InputEngine::MB_ICON_Exclamation: options |= MB_ICONEXCLAMATION;
		break;
	case InputEngine::MB_ICON_Warning: options |= MB_ICONWARNING;
		break;
	case InputEngine::MB_ICON_Information: options |= MB_ICONINFORMATION;
		break;
	case InputEngine::MB_ICON_Asterisk: options |= MB_ICONASTERISK;
		break;
	case InputEngine::MB_ICON_Question: options |= MB_ICONQUESTION;
		break;
	case InputEngine::MB_ICON_Stop: options |= MB_ICONSTOP;
		break;
	case InputEngine::MB_ICON_Error: options |= MB_ICONERROR;
		break;
	case InputEngine::MB_ICON_Hand: options |= MB_ICONHAND;
		break;
	case InputEngine::MB_ICON_None: // To not set an icon, just do not set the flag
		break;

	default: 
		break;
	}

	switch (DefaultBtn)
	{
	case InputEngine::MB_DEFAULTBUTTON_1: options |= MB_DEFBUTTON1;
		break;
	case InputEngine::MB_DEFAULTBUTTON_2: options |= MB_DEFBUTTON2;
		break;
	case InputEngine::MB_DEFAULTBUTTON_3: options |= MB_DEFBUTTON3;
		break;
	case InputEngine::MB_DEFAULTBUTTON_4: options |= MB_DEFBUTTON4;
		break;

	default:
		break;
	}

	int r = MessageBoxA(nullptr, Text, Title, options);

	switch (r)
	{
	case IDABORT: return MB_RETURN_Abort;
	case IDCANCEL: return MB_RETURN_Cancel;
	case IDCONTINUE: return MB_RETURN_Continue;
	case IDIGNORE: return MB_RETURN_Ingnore;
	case IDNO: return MB_RETURN_No;
	case IDOK: return MB_RETURN_OK;
	case IDRETRY: return MB_RETURN_Retry;
	case IDTRYAGAIN: return MB_RETURN_TryAgain;
	case IDYES: return MB_RETURN_Yes;


	default: return MB_RETURN_OK;
	}
#else
#error OS not implemented
#endif
}
