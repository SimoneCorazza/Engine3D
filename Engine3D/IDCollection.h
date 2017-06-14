#pragma once

#include <map>

//Classe che permette di racchiudere in se una collezione di oggetti identificati da interi che vengono gestiti dalla classe
template <class T>
class IDCollection
{
	unsigned int counter; //Contatore degli ID
	std::map<unsigned int, T> dictionary;

	public:
		IDCollection()
		{
			counter = 1;
		}

		~IDCollection()
		{
			dictionary.clear();
		}


	public:

		//Inserisce un nuovo elemento nella collezione e ne ritorna l'identificatore
		unsigned int InsertNew(T E)
		{
			dictionary[counter] = E;
			return counter++;
		}

		//Ottiene l'elemento con l'ID indicato
		T GetEl(int ID) const
		{
			if (Present(ID))
				return dictionary.find(ID)->second;
			else
				throw "Element not found";
		}

		//Rimuove l'elemento indicato dalla collezione
		//Nel caso in cui l'elemento non viene trovato genera un'eccezione
		void Remove(int ID)
		{
			dictionary.erase(ID);
		}

		//Indica se l'elemento con l'ID indicato è presente
		bool Present(int ID) const
		{
			return dictionary.find(ID) != dictionary.end();
		}

		//Ottiene gli Items che compongono la collezione
		std::vector<T> getItems() const
		{
			std::vector<T> v;
			std::map<int, T>::const_iterator it = dictionary.begin();
			while (it != dictionary.end())
			{
				v.push_back(it->second);
				it++;
			}
			return v;
		}

		//Ottiene il prossimo ID disponibile che andrà utilizzato per il prossimo elemento
		unsigned int getNextID()
		{
			return counter;
		}
};

