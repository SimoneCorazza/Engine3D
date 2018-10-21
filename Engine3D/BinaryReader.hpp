#pragma once

#include <iostream>
#include <fstream>

// Class that simplify reading from a binary file
class BinaryReader
{
	std::ifstream fs;

	public:
		// Opens a new file
		// @param[in] File - Path of the file to open
		BinaryReader(const char* File);

		~BinaryReader();

	public:

		// Gets a flag indicating whether the file is open
		bool IsOpen() const;

		// Close the file
		void Close();

		// Reads a 32 bit signed integer, shifting the stream forward of 4 bytes
		int ReadInt32();

		// Reads a 32 bit floating point, shifting the stream forward of 4 bytes
		float ReadSingle();

		// Reads a string of fixed size
		// @param [in] Size - Numbers of characters to read (> 0)
		// @return Returns an array of charactes with length Size (must be
		//		delete by the caller)
		char* ReadFixedString(size_t Size);

		// Read the next character from the stream
		char ReadChar();

		// Read a string of unspecified length. This function stop the read
		// procedure at the end of file or when at the character '\0'.
		char* ReadString();
};

