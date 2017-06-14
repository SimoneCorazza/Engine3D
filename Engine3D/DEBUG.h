/*
File che ha lo scopo di aggiungere delle utility per il debug dell'applicazione
*/
#pragma once

#include <iostream>

//---- PER IL DEBUG ----


//Messaggio di log delleazioni ritenute importanti
#ifdef _DEBUG
#define LOG(c, ...) do { printf("LOG: "); printf(c, ##__VA_ARGS__); printf("\n"); }while(0)
#else
#define LOG(C, ...)
#endif

//Messaggio di errore recuperabile: informa che è avvenuto un errore ma che l'esecuzione può continuare
#ifdef _DEBUG
#define ERROR(c, ...) do { printf("ERROR: "); printf(c, ##__VA_ARGS__); printf("\n"); } while(0)
#else
#define ERROR(c, ...)
#endif

//Errore di programmazione inaspettato dovuto a un'input inaspettatamente diverso da quello desiderato
//Emula il comportamento ad <assert.h>
#ifdef _DEBUG
#define ASSERT(condition, message)  do { if(!(condition)) { printf("ASSERT: "); printf(message); __debugbreak(); } } while(0) //(void)( (!!(condition)) && (message) ) )
#else
#define ASSERT(condition, message)
#endif

//---- PER LA RELESE -----

//Consente di mostrare un'errore in console nel caso siamo in debug altrimenti di mostrarlo in una MessageBox se si è inrelese
//per poi chiudere l'applicazione
void RELEASE_CLOSE(const char* C);




//---- TEMPO IMPIEGATO ----

//Consente di memorizzare lo stato di tempo attuale, per poi ottenerlo in seguito
void Time_Now();

//Estrae l'ultimo tempo inserito
float Time_Pop();

//Consente di estrarre l'ultimo tempo inserito e di ottenerlo scritto in console
//con il messaggio indicato
#define TIME_POP(c, ...) do { printf("TIME "); printf(c, ##__VA_ARGS__); printf(" %f sec\n", Time_Pop()); } while(0)