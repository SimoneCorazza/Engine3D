#pragma once

#include <vector>

#include "UIElement.h"

//Classe che rappresenta l'interfaccia utente
class UI
{
	std::vector<UIElement*> uiElements; //Elementi dell'interfaccia

	public:
		UI();
		~UI();

	public:

		//Aggiunge un elemento dell'interfaccia nell'UI
		//@param[in] UIElement - Elemento da aggiungere
		void Add(UIElement& UIElement);

		//Ottiene gli elementi dell'interfaccia
		const std::vector<UIElement*>& getUIElements();
};

