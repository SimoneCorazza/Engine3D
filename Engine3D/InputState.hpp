#pragma once

#include <glm\glm.hpp>

#include "IE_CursorMode.hpp"
#include "Point2.hpp"

#include "InputEngine.hpp"

struct GLFWwindow;

// Class that allows access to input devices and change in their status
class InputState
{
	// Allow the input manager to access the class completely
	friend class InputEngine;

	GLFWwindow* window; // Window to manage the input
	bool invalidated; // If true, indicate that this can not set the inputs

	// Struct that stores the status of a generic key
	struct KeyState
	{
		bool down; // Indicates if the key in the previous update was up and is now down
		bool up; // Indicates if the key in the previous update was down and is now up
		bool pressed; // Indicates if the key is pressed
	};

	// --- KEYBOARD

	// Oversized array (as not all cells are used) that memorize the state of
	// the keyboard keys the index in the array represents the ID of a key
	// according to GLFW
	KeyState* keyboard;

	// --- MOUSE

	// Cursor position
	Point2 cursor;

	// Mouse wheel state when this state was taken
	Point2 scrollWheel;

	// Number of scrolls done to the mouse wheel from the previous state
	Point2 delteScrollWheel;

	// Status of mouse buttons
	KeyState* mouse;

	// Current cursor mode
	IE_CursorMode cursorMode;

	// --- JOYSTICK

	public:

		// Class that represents a state of a Joystick
		class JoystickState
		{
			friend class InputState;

			// Status of the joystick buttons (the length of the array varies
			// from Joystick to Joystick)
			KeyState* buttons;
			// Number of joystick buttons
			size_t countButt;

			// Status of the joystick axes
			float* axes;
			// Number of joystick axes
			size_t countAxes;

			private:
				JoystickState();
			public:
				~JoystickState();

			public:

				// Indicates if the button has been raised from the previous state
				// @param[in] I - Base index 0 which identifies the button
				bool IsButtonUp(size_t I) const;

				// Indicates whether the button was pressed from the previous state
				// @param[in] I - Base index 0 which identifies the button
				bool IsButtonDown(size_t I) const;

				// Indicates if the button is pressed
				// @param[in] I - Base index 0 which identifies the button
				bool IsButtonPressed(size_t I) const;

				// Get the number of joystick buttons
				size_t getNumButtons() const;


				// Gets the status of the indicated axis
				// @param[in] I - Base index 0 indicating the axis of the Joystick
				float getAxes(size_t I) const;

				// Gets the first analog of the controller
				// @NOTE: if the joystick does not have enough axes (at least two) it will come back (0, 0)
				glm::vec2 getFirstAnalog() const;

				// Gets the second analog of the controller
				// @NOTE: if the joystick does not have enough axes (at least four) it will return (0, 0)
				glm::vec2 getSecondAnalog() const;

				// Gets the number of axes of the joystick
				size_t getNumAxes() const;


			private:
				// Gets the current state of a joystick
				// @param[in] GLFW_JoystickID - Joystick ID according to GLFW
				// @param[in] Prec - Previous state of the Joystick (with the same ID), null if no previous state exists
				// @return The current state of the joystick; if the indicated ID is not present, returns null
				// @NOTE: Method created for the friend class InputState
				static JoystickState* GetJoystickState(int GLFW_JoystickID, const JoystickState* Prec);
		};

	private:

		// Array for joysticks (oversized array)
		// the array index represents the Joystick ID assigned by GLFW
		// if one Joystick is not present their cell will be null
		JoystickState** joysticks;
		// Number of connected Joysticks
		size_t connectedJoysticks;


	// --- WINDOW

	// Size of the associated window
	Point2 windowSize;
	// Indicates if the window size has been changed since the last update (but
	// not if it has size (0, 0))
	bool windowSizeChanged;
	// Whether the window area is valid (the surfacearea in pixels is> 0)
	bool windowSurfaceValid;


	private:
		InputState();
	public:
		~InputState();


	public:

		// ---- APPLICATION WINDOW -----

		// Gets the size of the actual window in pixels
		Point2 getWindowSize() const;

		// Gets a flag indicating whether the window is currently minimized (window size (0, 0))
		// or simply that the window has invalid size (ie it has been reduced to such an extent that it makes a dimension 0)
		bool WindowSurfaceValid() const;

		// Gets a flag indicating that the game window has been resized but not if the size
		// the window has become null (area in pixel equal to 0)
		bool WindowResized() const;



		// ---- KEYBOARD -----

		// Gets a flag indicating whether the key was released in this state
		// @param[in] GLFW_KeyCode - Key to check (GLFW-related ID)
		bool IsKeyUp(int GLFW_KeyCode) const;

		// Gets a flag indicating whether the key was pressed in this state
		// @param[in] GLFW_KeyCode - Key to check (GLFW-related ID)
		bool IsKeyDown(int GLFW_KeyCode) const;

		// Gets a flag indicating whether the key was currently pressed by the user
		// @param[in] GLFW_KeyCode - Key to check (GLFW-related ID)
		bool IsKeyPressed(int GLFW_KeyCode) const;


		// ---- MOUSE ----

		// Gets a flag indicating whether the mouse button was released in this state
		// @param [in] GLFW_MouseButtonCode - Button of the mouse to be checked (ID related to GLFW)
		bool IsMouseButtonUp(int GLFW_MouseButtonCode) const;

		// Gets a flag indicating whether the mouse button was pressed in this state
		// @param [in] GLFW_MouseButtonCode - Button of the mouse to be checked (ID related to GLFW)
		bool IsMouseButtonDown(int GLFW_MouseButtonCode) const;

		// Gets a flag indicating whether the mouse button was currently pressed by the user
		// @param [in] GLFW_MouseButtonCode - Button of the mouse to be checked (ID related to GLFW)
		bool IsMouseButtonPressed(int GLFW_MouseButtonCode) const;

		// Gets the cursor position in the window
		Point2 getCursorPosition() const;

		// Sets the position of the cursor relative to the current window
		// @param[in] P - Position of the cursor in pixels in the window
		void setCursorPosition(const Point2& P);

		// Sets the position of the cursor relative to the current window
		// @param[in] X - X coordinate of the pixel position of the cursor in the window
		// @param[in] Y - Y coordinate of the pixel position of the cursor in the window
		// @NOTE: The opeation can only be successful if this represents the last state of the input
		void setCursorPosition(int x, int y);

		// Sets the mode in which the cursor will be treated
		// @NOTE: The opeation can only be successful if this represents the last state of the input
		void setCursorMode(IE_CursorMode CursorMode);

		// Gets the cursor mode currently set in the engine
		IE_CursorMode getCursorMode() const;

		// Gets how mutch the mouse wheel moved from the last state on the X axis
		// @return Integer indicating how much the wheel has moved on the X axis.
		//		Positive value if moved to the left negative otherwise.
		int getScrollWheelX() const;

		// It gets how much the mouse wheel moved from the last state on the Y axis
		// @return Integer indicating how much the wheel has moved on the Y axis.
		//		Positive value if moved upwards negative otherwise.
		int getScrollWheelY() const;

		// It gets how much the mouse wheel has moved since the last state
		// @return Integer indicating how much the wheel has moved
		Point2 getScrollWheel() const;

		// --- JOYSTICK ---

		// Gets the number of connected joysticks
		size_t getNumConnectedJoystick() const;

		// Gets the status of the indicated Joystick
		// @param[in] GLFW_JoystickID - ID according to GLFW of the Joystick
		// @return Joystick status or null if the Joystick with ID shown is not present
		// @NOTE: The pointer deletion is managed by this class
		const JoystickState* getJoystickState(int GLFW_JoystickID) const;

		// Gets an array with the GLFW IDs of connected Joysticks
		// @return array containing the GLFW IDs of the connected Joysticks, null if there is no joystik
		// @NOTE: Management of the returned pointer is delegated to the user
		//		(release the memory with delete [])
		const int* getJoystickIDs() const;


	private:

		// Indicates that this is no longer the last most recent state (there is a newer one)
		// and therefore to this instance the possibility of modifying the input status is deprived
		// @NOTE: Created to be used by the friendEngineEngine class
		void Invalidate();

		// Gets an InputState object for the state of the current input
		// @param [in] Window - Window to get input from
		// @param [in] PrecState - State prior to this, if there is no null pass
		// @NOTE: Created to be used by the friendEngineEngine class
		static InputState* GetState(GLFWwindow* Window, const InputEngine* InputEngine, const InputState* PrecState);
};

