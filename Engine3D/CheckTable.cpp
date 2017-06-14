#include "CheckTable.h"



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

	if (table[index] == nullptr) //Caso non è stato creato l'array
	{
		table[index] = new std::vector<KeyType>();
		table[index]->push_back(K); //Inserisco il valore
		return false; //Indico di non averlo trovato
	}
	else
	{
		//Cerco l'elemento nel sotto array:
		std::vector<KeyType>* vec = table[index];
		size_t i = 0;
		while (i < vec->size() && (*vec)[i] != K)
			i++;
		
		if (i == vec->size()) //Elemento non trovato
		{
			vec->push_back(K); //Inserisco l'elemento siccome non presente
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
		for (size_t i = 0; i < tableSize; i++) //Elimino i sotto-arry istanziati
			delete table[i];
		delete table;
	}
	tableSize = PredictedSize;
	table = new std::vector<KeyType>*[tableSize];
	for (size_t i = 0; i < tableSize; i++) //Inizializzo i vettori a null
		table[i] = nullptr;
}

inline size_t CheckTable::HashFunction(const KeyType & K)
{
	return K % tableSize;
}
