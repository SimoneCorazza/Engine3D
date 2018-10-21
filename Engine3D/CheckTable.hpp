#pragma once

// #include <hash_map>
#include <vector>



// A class that represents a table that associates a value with a key
// checked or not cheked (true or false) based on the presence of the key in the table
class CheckTable
{
	typedef int KeyType; // Typology for the key (must be numeric and basic)

	/*
	Implementation note: used concatenated hash
	*/

	size_t tableSize;
	std::vector<KeyType>** table;

	public:

		// Instantiate a table with expected size of 1
		CheckTable();

		// @param[in] PredictedSize - Expected table size
		CheckTable(size_t PredictedSize);

		~CheckTable();

	public:

		// Inserts the element if not yet present
		// @param[in] K - Element to be inserted
		// @return True if the element was already inserted, false otherwise
		virtual bool Check(const KeyType& K);

		// Reset the data structure
		// @param[in] PredictedSize - Expected table size
		void Reset(size_t PredictedSize);

	private:

		// @param[in] K - Key
		// @return Index based 0 of the table where to find the ID
		inline size_t HashFunction(const KeyType& K);
};

