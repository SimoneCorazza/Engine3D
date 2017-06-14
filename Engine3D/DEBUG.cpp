#include "DEBUG.h"



#include <stdio.h>

#include <GLFW\glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW\glfw3native.h>
#include <Windows.h>

#include <stack>
#include <chrono>

//---- PER IL DEBUG ----

/*

//Inserisce un breaking point nella riga indicata
void Debug_BreakPoint()
{
#ifdef _DEBUG
	__debugbreak();
#else
	//Nothing
#endif
}

//Mostra un messaggio d'errore e inserisce un breaking point
void Debug_ErrorBreak(const char* C)
{
#ifdef _DEBUG
	printf(C);
	printf("\n");
	Debug_BreakPoint();
#else
	//Nothing
#endif
}

//Stampa un messaggio sullo standard output seguito da un a capo
void Log(const char* C)
{
#ifdef _DEBUG
	printf(C);
	printf("\n");
#else
	//Nothing
#endif
}
*/

/*
//Stampa sullo standard output un'errore non fatale
void Debug_Error(const char* C)
{
#ifdef _DEBUG
	printf("ERROR: ");
	printf(C);
	printf("\n");
#else
	//Nothing
#endif
}
*/

//---- PER LA RELESE -----


//Consente di mostrare un'errore in console nel caso siamo in debug altrimenti di mostrarlo in una MessageBox se si è inrelese
//per poi chiudere l'applicazione
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


//---- TEMPO IMPIEGATO ----

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
		timeStack.pop(); //Elimino l'ultima  ora
		return seconds.count();
	}
}