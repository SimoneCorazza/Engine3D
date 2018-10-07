#pragma once

#include <map>

// Class that represents an editor for the values ​​of a map
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

		// Indicates if the collection is over
		bool hasNext()
		{
			return it != end;
		}

		// Gets the next item in the collection
		T next()
		{
			if (!hasNext())
				throw;

			T r = it->second;
			it++;
			return r;
		}

		// Gets the size of the collection
		size_t size()
		{
			return s;
		}

		// Allows you to reset the iterator, restarting it from the beginning of the cluster
		void reset()
		{
			it = begin;
		}

};
