/*
File that aims to add utilities for debugging the application
*/
#pragma once

#include <iostream>

// ---- FOR THE DEBUG ----


// Log message of the assessments deemed important
#ifdef _DEBUG
#define LOG(c, ...) do { printf("LOG: "); printf(c, ##__VA_ARGS__); printf("\n"); }while(0)
#else
#define LOG(C, ...)
#endif

// Recoverable error message: informs you that an error occurred but that execution can continue
#ifdef _DEBUG
#define ERROR(c, ...) do { printf("ERROR: "); printf(c, ##__VA_ARGS__); printf("\n"); } while(0)
#else
#define ERROR(c, ...)
#endif

// Unexpected programming error due to an unexpectedly different input from the one desired
// Emulates the behavior to <assert.h>
#ifdef _DEBUG
#define ASSERT(condition, message)  do { if(!(condition)) { printf("ASSERT: "); printf(message); __debugbreak(); } } while(0) // (void) ((!! (condition)) && (message)))
#else
#define ASSERT(condition, message)
#endif

// ---- FOR RELEASE -----

// Lets show an error in the console if we are debugging otherwise to show it in a MessageBox if it is in relese
// and then close the application
void RELEASE_CLOSE(const char* C);




// ---- THE TIME SPENT ON ----

// It allows you to store the current time status, and then obtain it later
void Time_Now();

// Extracts the last inserted time
float Time_Pop();

// It allows you to extract the last inserted time and get it written in the console
// with the indicated message
#define TIME_POP(c, ...) do { printf("TIME "); printf(c, ##__VA_ARGS__); printf(" %f sec\n", Time_Pop()); } while(0)