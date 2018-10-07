#include "UI.hpp"



UI::UI()
{
}


UI::~UI()
{
}

void UI::Add(UIElement& UIElement)
{
	uiElements.push_back(&UIElement);
}

const std::vector<UIElement*>& UI::getUIElements()
{
	return uiElements;
}
