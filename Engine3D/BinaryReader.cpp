#include "BinaryReader.hpp"

#include <vector>


BinaryReader::BinaryReader(const char* File)
{
	fs.open(File, std::ios::binary | std::ios::in);
}


BinaryReader::~BinaryReader()
{
	
}

bool BinaryReader::IsOpen() const
{
	return fs.is_open();
}

void BinaryReader::Close()
{
	fs.close();
}

int BinaryReader::ReadInt32()
{
	int i;
	fs.read((char*)&i, 4);

	return i;
}

float BinaryReader::ReadSingle()
{
	float fl;
	fs.read((char*)&fl, 4);

	return fl;
}

char* BinaryReader::ReadFixedString(size_t Size)
{
	char* str = new char[Size];
	for (int i = 0; i < Size; i++)
		str[i] = ReadChar();
	return str;
}

char BinaryReader::ReadChar()
{
	char c = '\0';
	fs.read(&c, 1);

	return c;
}

char* BinaryReader::ReadString()
{
	std::vector<char> str;

	char c;
	do
	{
		c = ReadChar();
		str.push_back(c);
	} while (c != '\0');
	
	char* s = new char[str.size()];
	_memccpy(s, &str[0], 0, sizeof(char) * str.size());

	return s;
}