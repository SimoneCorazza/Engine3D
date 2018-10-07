#include "DEBUG.hpp"



#include <stdio.h>

#include <GLFW\glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW\glfw3native.h>
#include <Windows.h>

#include <stack>
#include <chrono>

// ---- FOR THE DEBUG ----

/*

// Inserts a breaking point in the indicated line
void Debug_BreakPoint()
{
#ifdef _DEBUG
	__debugbreak();
#else
	// nothing
#endif
}

// Show an error message and insert a breaking point
void Debug_ErrorBreak(const char* C)
{
#ifdef _DEBUG
	printf(C);
	printf("\n");
	Debug_BreakPoint();
#else
	// nothing
#endif
}

// Print a message on standard output followed by a new one
void Log(const char* C)
{
#ifdef _DEBUG
	printf(C);
	printf("\n");
#else
	// nothing
#endif
}
*/

/*
// Print on the standard output a non-fatal error
void Debug_Error(const char* C)
{
#ifdef _DEBUG
	printf("ERROR: ");
	printf(C);
	printf("\n");
#else
	// nothing
#endif
}
*/

// ---- FOR RELEASE -----


// Lets show an error in the console if we are debugging otherwise to show it in a MessageBox if it is inrelese
// and then close the application
void RELEASE_CLOSE(const char* C)
{
#ifdef _DEBUG
	printf("FATAL ERROR: ");
	printf(C);
	printf("\n");
	__debugbreak();
#else
	GLFWwindow* w = glfwGetCurrentContext();
	if (w == nullptr)
	{
		printf("FATAL ERROR: ");
		printf(C);
		printf("\n");
	}
	else
	{
		int leng = strlen(C);
		WCHAR* str = new WCHAR[leng];
		MultiByteToWideChar(0, 0, C, leng + 1, str, leng + 1);
		MessageBox((HWND)glfwGetWindowUserPointer(w), str, TEXT("Fatal error"), MB_OK);
		delete str;
	}
#endif

	exit(EXIT_FAILURE);
}


// ---- THE TIME SPENT ON ----

std::stack<  std::chrono::time_point<std::chrono::high_resolution_clock>  > timeStack;

void Time_Now()
{
	timeStack.push(std::chrono::high_resolution_clock::now());
}

float Time_Pop()
{
	if (timeStack.empty())
		return -1.0f;
	else
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> curr = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> seconds = std::chrono::duration_cast<std::chrono::duration<float>>(curr - timeStack.top());
		timeStack.pop(); // I'll take the last hour
		return seconds.count();
	}
}