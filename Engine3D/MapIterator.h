#pragma once

#include <map>

//Classe che rappresenta un'itoratore per i valori di una map
template <class K, class T>
class MapIterator
{
	typename std::map<K, T>::const_iterator begin;
	typename std::map<K, T>::const_iterator it;
	typename std::map<unsigned int, T>::const_iterator end;
	size_t s;
	
	public:
		MapIterator(const std::map<K, T>& Map)
		{
			begin = Map.begin();
			it = begin;
			end = Map.end();
			s = Map.size();
		}

		~MapIterator()
		{

		}

	public:

		//Indica se la collezione è finita
		bool hasNext()
		{
			return it != end;
		}

		//Ottiene il prossimo elemento della collezione
		T next()
		{
			if (!hasNext())
				throw;

			T r = it->second;
			it++;
			return r;
		}

		//Ottiene la dimensione della collezione
		size_t size()
		{
			return s;
		}

		//Consente di resettare l'iteratore, facendolo ripartire dall'inizio della clollezione
		void reset()
		{
			it = begin;
		}

};
