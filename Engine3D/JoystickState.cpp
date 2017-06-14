#include "InputState.h"

#include <GLFW\glfw3.h>

InputState::JoystickState::JoystickState()
{
	buttons = nullptr;
	countButt = 0;
	axes = nullptr;
	countAxes = 0;
}


InputState::JoystickState::~JoystickState()
{
	delete buttons;
	delete axes;
}




bool InputState::JoystickState::IsButtonUp(size_t I) const
{
	if (I < 0 || I >= countButt)
		return false;
	else
		return buttons[I].up;
}

bool InputState::JoystickState::IsButtonDown(size_t I) const
{
	if (I < 0 || I >= countButt)
		return false;
	else
		return buttons[I].down;
}

bool InputState::JoystickState::IsButtonPressed(size_t I) const
{
	if (I < 0 || I >= countButt)
		return false;
	else
		return buttons[I].pressed;
}

size_t InputState::JoystickState::getNumButtons() const
{
	return countButt;
}

float InputState::JoystickState::getAxes(size_t I) const
{
	if (I < 0 || I >= countAxes)
		return 0;
	else
		return axes[I];
}

glm::vec2 InputState::JoystickState::getFirstAnalog() const
{
	if (getNumAxes() >= 2)
		return glm::vec2(getAxes(0), getAxes(1));
	else
		return glm::vec2(0, 0);
}

glm::vec2 InputState::JoystickState::getSecondAnalog() const
{
	if (getNumAxes() >= 4)
		return glm::vec2(getAxes(2), getAxes(3));
	else
		return glm::vec2(0, 0);
}

size_t InputState::JoystickState::getNumAxes() const
{
	return countAxes;
}

InputState::JoystickState * InputState::JoystickState::GetJoystickState(int GLFW_JoystickID, const JoystickState* Prec)
{
	//Caso il joystick desiderato non sia presente
	if (GLFW_JoystickID < 0 || GLFW_JoystickID > GLFW_JOYSTICK_LAST ||
		glfwJoystickPresent(GLFW_JoystickID) == GL_FALSE)
		return nullptr;
	else
	{
		InputState::JoystickState* j = new InputState::JoystickState();

		//Prendo gli input:
		int numAxes;
		const float* axes = glfwGetJoystickAxes(GLFW_JoystickID, &numAxes);

		int numBtn;
		const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JoystickID, &numBtn);

		//Caso il joystick precedente abbia parametri diverso da questi (= sicuramente non è lo stesso joystick di prima)
		if (Prec != nullptr && ((size_t)numAxes != Prec->countAxes || (size_t)numBtn != Prec->countButt))
			return nullptr;

		//Settaggio per gli assi:
		j->countAxes = (size_t)numAxes;
		j->axes = new float[j->countAxes]; //Istanzio l'array degli assi
		for (size_t i = 0; i < j->countAxes; i++) //Copio l'array passato da GLFW
			j->axes[i] = axes[i];

		//Settaggio per i bottoni:
		j->countButt = (size_t)numBtn;
		j->buttons = new KeyState[j->countButt];

		if (Prec == nullptr)
		{
			for (size_t i = 0; i < j->countButt; i++)
			{
				j->buttons[i].pressed = buttons[i] == GLFW_PRESS;
				j->buttons[i].down = j->buttons[i].pressed;
				j->buttons[i].up = false;
			}
		}
		else
		{
			for (size_t i = 0; i < j->countButt; i++)
			{
				bool p = buttons[i] == GLFW_PRESS;
				j->buttons[i].pressed = p;
				j->buttons[i].down = p && !Prec->IsButtonPressed(i);
				j->buttons[i].up = !p && Prec->IsButtonPressed(i);
			}
		}

		return j;
	}
}
