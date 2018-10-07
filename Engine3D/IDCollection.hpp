#pragma once

#include <map>

// Class that allows to enclose in itself a collection of objects identified by integers that are managed by the class
template <class T>
class IDCollection
{
	unsigned int counter; // ID counter
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

		// Inserts a new item into the collection and returns the identifier
		unsigned int InsertNew(T E)
		{
			dictionary[counter] = E;
			return counter++;
		}

		// Gets the item with the indicated ID
		T GetEl(int ID) const
		{
			if (Present(ID))
				return dictionary.find(ID)->second;
			else
				throw "Element not found";
		}

		// Removes the item indicated by the collection
		// In the event that the element is not found, it generates an exception
		void Remove(int ID)
		{
			dictionary.erase(ID);
		}

		// Indicates whether the item with the indicated ID is present
		bool Present(int ID) const
		{
			return dictionary.find(ID) != dictionary.end();
		}

		// Gets the Items that make up the collection
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

		// Gets the next available ID that will be used for the next item
		unsigned int getNextID()
		{
			return counter;
		}
};

