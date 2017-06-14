#pragma once

//#include <hash_map>
#include <vector>



//Classe che rappresenta una tabella che associa a un chiave un valore
//checked o non cheked (vero o falso) in base alla presenza della chiave nella tabella
class CheckTable
{
	typedef int KeyType; //Tipologia per la chiave (deve essere numerico e di tipo base)

	/*
	Nota implementativa: usato hash concatenato
	*/

	size_t tableSize;
	std::vector<KeyType>** table;

	public:

		//Istanzia una tabella con dimensione prevista di 1
		CheckTable();

		//@param[in] PredictedSize - Dimensione prevista della tabella
		CheckTable(size_t PredictedSize);

		~CheckTable();

	public:

		//Inserisce l'elemento se non ancora presente
		//@param[in] K - Elemento da inserire
		//@return True se l'elemento era già inserito, false altrimenti
		virtual bool Check(const KeyType& K);

		//Resetta la struttura dati
		//@param[in] PredictedSize - Dimensione prevista della tabella
		void Reset(size_t PredictedSize);

	private:

		//@param[in] K - Chiave
		//@return Indice in base 0 della tabella dove trovare la l'ID
		inline size_t HashFunction(const KeyType& K);
};

