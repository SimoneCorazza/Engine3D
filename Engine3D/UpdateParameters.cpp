#include "UpdateParameters.hpp"



UpdateParameters::UpdateParameters(float ElapsedTime, InputState* InputState)
{
	elapsedTime = ElapsedTime;
	inputState = InputState;
}


UpdateParameters::~UpdateParameters()
{
}

float UpdateParameters::getElapsedTime() const
{
	return elapsedTime;
}

InputState * UpdateParameters::getInputState() const
{
	return inputState;
}
