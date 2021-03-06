#include "InputState.hpp"

#include <GLFW\glfw3.h>
#include "DEBUG.hpp"

#include <vector>

InputState::InputState()
{
	keyboard = nullptr;
	mouse = nullptr;
	joysticks = nullptr;
	connectedJoysticks = 0;
	invalidated = false;
}


InputState::~InputState()
{
	delete keyboard;
	delete mouse;

	for (int i = 0; i <= GLFW_JOYSTICK_LAST; i++)
		delete joysticks[i];

	delete[] joysticks;
}






InputState* InputState::GetState(GLFWwindow* Window, const InputEngine* InputEngine, const InputState * PrecState)
{
	InputState* r = new InputState();
	r->keyboard = new KeyState[GLFW_KEY_LAST + 1];
	r->mouse = new KeyState[GLFW_MOUSE_BUTTON_LAST + 1];
	r->joysticks = new InputState::JoystickState*[GLFW_JOYSTICK_LAST + 1];
	r->window = Window;

	// I get INDEPENDENT parameters from the previous state of the class
	int w, h;
	glfwGetWindowSize(Window, &w, &h);
	r->windowSize.x = w;
	r->windowSize.y = h;
	// Chech if the surface is valid
	r->windowSurfaceValid = w * h > 0;

	double x, y;
	glfwGetCursorPos(Window, &x, &y);
	r->cursor.x = (int)x;
	r->cursor.y = (int)y;

	// I get EMPLOYMENT parameters from the previous state of the class

	if (PrecState == nullptr)
	{
		for (size_t i = 0; i <= GLFW_KEY_LAST; i++) // For the keyboard
		{
			r->keyboard[i].pressed = glfwGetKey(Window, i) == GLFW_PRESS;
			r->keyboard[i].down = r->keyboard[i].pressed;
			r->keyboard[i].up = false;
		}

		for (size_t i = 0; i <= GLFW_MOUSE_BUTTON_LAST; i++) // For the mouse
		{
			r->mouse[i].pressed = glfwGetMouseButton(Window, i) == GLFW_PRESS;
			r->mouse[i].down = r->mouse[i].pressed;
			r->mouse[i].up = false;
		}

		for (size_t i = 0; i <= GLFW_JOYSTICK_LAST; i++) // For the joysticks
		{
			r->joysticks[i] = InputState::JoystickState::GetJoystickState(i, nullptr);
			if(r->joysticks[i] != nullptr) // Increase the number of connected joysticks
				r->connectedJoysticks++;
		}

		r->cursorMode = IE_CursorMode::IE_CursorMode_Normal; // Default setting (the deduction may be incorrect)
		r->windowSizeChanged = false;
	}
	else
	{
		// KEYBOARD
		for (size_t i = 0; i <= GLFW_KEY_LAST; i++)
		{
			bool p = glfwGetKey(Window, i) == GLFW_PRESS;
			r->keyboard[i].pressed = p;
			r->keyboard[i].down = p && !PrecState->IsKeyPressed(i);
			r->keyboard[i].up = !p && PrecState->IsKeyPressed(i);
		}

		// MOUSE
		for (size_t i = 0; i <= GLFW_MOUSE_BUTTON_LAST; i++)
		{
			bool p = glfwGetMouseButton(Window, i) == GLFW_PRESS;
			r->mouse[i].pressed = p;
			r->mouse[i].down = p && !PrecState->IsMouseButtonPressed(i);
			r->mouse[i].up = !p && PrecState->IsMouseButtonPressed(i);
		}

		// JOYSTICKS
		for (size_t i = 0; i <= GLFW_JOYSTICK_LAST; i++)
		{
			r->joysticks[i] = InputState::JoystickState::GetJoystickState(i, PrecState->getJoystickState(i));
			// Increase the number of connected joysticks
			if (r->joysticks[i] != nullptr)
				r->connectedJoysticks++;
		}

		r->cursorMode = PrecState->getCursorMode();
		r->windowSizeChanged = r->windowSize != PrecState->getWindowSize() && r->windowSurfaceValid;

		r->scrollWheel = InputEngine->getScroolWheelState();
		r->delteScrollWheel.x = r->scrollWheel.x - PrecState->scrollWheel.x;
		r->delteScrollWheel.y = r->scrollWheel.y - PrecState->scrollWheel.y;
	}
	

	return r;
}

Point2 InputState::getWindowSize() const
{
	return windowSize;
}

bool InputState::WindowSurfaceValid() const
{
	return windowSurfaceValid;
}

bool InputState::WindowResized() const
{
	return windowSizeChanged;
}

bool InputState::IsKeyUp(int GLFW_KeyCode) const
{
	if (GLFW_KeyCode < 0 || GLFW_KeyCode > GLFW_KEY_LAST)
		return false;
	else
		return keyboard[GLFW_KeyCode].up;
}

bool InputState::IsKeyDown(int GLFW_KeyCode) const
{
	if (GLFW_KeyCode < 0 || GLFW_KeyCode > GLFW_KEY_LAST)
		return false;
	else
		return keyboard[GLFW_KeyCode].down;
}

bool InputState::IsKeyPressed(int GLFW_KeyCode) const
{
	if (GLFW_KeyCode < 0 || GLFW_KeyCode > GLFW_KEY_LAST)
		return false;
	else
		return keyboard[GLFW_KeyCode].pressed;
}

bool InputState::IsMouseButtonUp(int GLFW_MouseButtonCode) const
{
	if (GLFW_MouseButtonCode < 0 || GLFW_MouseButtonCode > GLFW_MOUSE_BUTTON_LAST)
		return false;
	else
		return mouse[GLFW_MouseButtonCode].up;
}

bool InputState::IsMouseButtonDown(int GLFW_MouseButtonCode) const
{
	if (GLFW_MouseButtonCode < 0 || GLFW_MouseButtonCode > GLFW_MOUSE_BUTTON_LAST)
		return false;
	else
		return mouse[GLFW_MouseButtonCode].down;
}

bool InputState::IsMouseButtonPressed(int GLFW_MouseButtonCode) const
{
	if (GLFW_MouseButtonCode < 0 || GLFW_MouseButtonCode > GLFW_MOUSE_BUTTON_LAST)
		return false;
	else
		return mouse[GLFW_MouseButtonCode].pressed;
}

Point2 InputState::getCursorPosition() const
{
	return cursor;
}

void InputState::setCursorPosition(const Point2 & P)
{
	setCursorPosition(P.x, P.y);
}

void InputState::setCursorPosition(int x, int y)
{
	if (!invalidated)
	{
		glfwSetCursorPos(window, (double)x, (double)y);
		cursor.x = x;
		cursor.y = y;
	}
}

void InputState::setCursorMode(IE_CursorMode CursorMode)
{
	if (!invalidated)
	{
		switch (CursorMode)
		{
		case IE_CursorMode::IE_CursorMode_Normal: glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); break;
		case IE_CursorMode::IE_CursorMode_Hide: glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); break;
		case IE_CursorMode::IE_CursorMode_Disabled: glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); break;

		default: ASSERT(false, "Case not known"); break;
		}

		cursorMode = CursorMode;
	}
}

IE_CursorMode InputState::getCursorMode() const
{
	return cursorMode;
}

int InputState::getScrollWheelX() const
{
	return delteScrollWheel.x;
}

int InputState::getScrollWheelY() const
{
	return delteScrollWheel.y;
}

Point2 InputState::getScrollWheel() const
{
	return delteScrollWheel;
}

size_t InputState::getNumConnectedJoystick() const
{
	return connectedJoysticks;
}

const InputState::JoystickState * InputState::getJoystickState(int GLFW_JoystickID) const
{
	if (GLFW_JoystickID < 0 && GLFW_JoystickID > GLFW_JOYSTICK_LAST)
		return nullptr;
	else
		return joysticks[GLFW_JoystickID];
}

const int * InputState::getJoystickIDs() const
{
	if (getNumConnectedJoystick() == 0)
		return nullptr;
	else
	{
		int* arr = new int[getNumConnectedJoystick()];
		int i = 0;
		size_t remainingJoy = getNumConnectedJoystick();
		while (remainingJoy > 0)
		{
			if (joysticks[i] != nullptr)
			{
				arr[getNumConnectedJoystick() - remainingJoy] = i;
				remainingJoy--;
			}
			i++;
		}
	}
}


void InputState::Invalidate()
{
	invalidated = true;
}
