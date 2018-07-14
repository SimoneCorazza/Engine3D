#pragma once

#include <iostream>
#include <fstream>

// Class that allows you to read a file as a binary file
class BinaryReader
{
	std::ifstream fs;

	public:
		// Opens a new file
		BinaryReader(const char* File);

		~BinaryReader();

	public:

		// Gets a flag indicating whether the file is open
		bool IsOpen() const;

		// It allows you to close the file
		void Close();

		// It reads the 32-bit continuums and converts it in full with sign
		int ReadInt32();

		// Read the next 32 bits and convert them to floating-point
		float ReadSingle();

		// Reads a string of fixed size
		// @param [in] Size - Numbers of characters to read> 0
		// @return Returns an array of size Size of the read characters (to be deleted later)
		char* ReadFixedString(size_t Size);

		// Read the next character from the stream
		char ReadChar();

		// Read a string
		char* ReadString();
};

