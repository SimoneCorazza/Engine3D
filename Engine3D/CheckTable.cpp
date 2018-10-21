#include "CheckTable.hpp"



CheckTable::CheckTable()
{
	table = nullptr;
	tableSize = 0;
	Reset(1);
}

CheckTable::CheckTable(size_t PredictedSize)
{
	table = nullptr;
	tableSize = 0;
	Reset(PredictedSize);
}


CheckTable::~CheckTable()
{
}

bool CheckTable::Check(const KeyType& K)
{
	int index = HashFunction(K);

	if (table[index] == nullptr) // Case has not been created the array
	{
		table[index] = new std::vector<KeyType>();
		table[index]->push_back(K); // I enter the value
		return false; // I indicate that I have not found it
	}
	else
	{
		// I look for the element in the sub array:
		std::vector<KeyType>* vec = table[index];
		size_t i = 0;
		while (i < vec->size() && (*vec)[i] != K)
			i++;
		
		if (i == vec->size()) // Element not found
		{
			vec->push_back(K); // I insert the element as not present
			return false;
		}
		else
			return true;
	}
}

void CheckTable::Reset(size_t PredictedSize)
{
	if (table != nullptr)
	{
		for (size_t i = 0; i < tableSize; i++) // I delete the instantiated sub-array
			delete table[i];
		delete table;
	}
	tableSize = PredictedSize;
	table = new std::vector<KeyType>*[tableSize];
	for (size_t i = 0; i < tableSize; i++) // Initialize the vectors to null
		table[i] = nullptr;
}

inline size_t CheckTable::HashFunction(const KeyType & K)
{
	return K % tableSize;
}
