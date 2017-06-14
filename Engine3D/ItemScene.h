#pragma once

#include "InputState.h"
class Scene;

//Rappresenta un elemento di una scena: Camera, Attore, ...
//che necessita di un identificatore e di un ID
class ItemScene
{
	friend Scene; //PER SETTARE I PARAMETRI: ID e scene

	unsigned int id; //ID dell'item; univoco nella scena
	Scene* scene; //Scena contenente l'item

	public:
		ItemScene();
		~ItemScene();


	public:

		//Ottiene l'ID del'item secondo la scena
		unsigned int getID() const;

		//Ottiene la scena contenente l'item
		const Scene* getScene();

		//Permette di rimuovere questo elemento dalla scena
		//NOTA: l'oggetto verrà distrutto (delete obj)
		void RemoveFromScene();

	protected:

		//Ottiene l'ultimo stato dell'input per la scena
		InputState* getInputState();
};

