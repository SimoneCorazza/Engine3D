#pragma once

class InputState;

// Immutable class that collects parameters to pass to the scene, actors and any
// another item to update
class UpdateParameters
{
	float elapsedTime;
	InputState* inputState;


	public:
		// @param[in] ElapsedTime - Time spent in seconds since the last update
		UpdateParameters(float ElapsedTime, InputState* InputState);
		~UpdateParameters();

	public:

		// Gets the time spent in seconds since the last Update
		float getElapsedTime() const;

		// Gets the status of the current input
		InputState* getInputState() const;

};

