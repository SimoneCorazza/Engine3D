#pragma once

#include <iostream>
#include <fstream>

//Classe che permette di leggere un file come file binario
class BinaryReader
{
	std::ifstream fs;

	public:
		//Apre un nuovo file
		BinaryReader(const char* File);

		~BinaryReader();

	public:

		//Ottiene un flag che indica se il file è aperto
		bool IsOpen() const;

		//Permette di chiudere il file
		void Close();

		//Legge i prosimi 32 bit e lo converte in intero con segno
		int ReadInt32();

		//Legge i prossimi 32 bit e li converte in floating-point
		float ReadSingle();

		//Legge una stringa di dimensione fissata
		//@param[in] Size - Numeri di caratteri da leggere > 0
		//@return Ritorna un'array di dimensione Size dei caratteri letti (da eliminare successivamente)
		char* ReadFixedString(size_t Size);

		//Legge il prossimo carattere dallo stream
		char ReadChar();

		//Legge una stringa
		char* ReadString();
};

