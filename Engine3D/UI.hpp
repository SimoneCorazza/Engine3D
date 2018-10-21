#pragma once

#include <vector>

#include "UIElement.hpp"

// Class representing the user interface
class UI
{
	// Interface elements
	std::vector<UIElement*> uiElements;

	public:
		UI();
		~UI();

	public:

		// Adds an interface element in the UI
		// @param[in] UIElement - Element to add
		void Add(UIElement* UIElement);

		// Gets the elements of the interface
		const std::vector<UIElement*>& getUIElements();
};

