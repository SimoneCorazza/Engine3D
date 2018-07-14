#pragma once

#include <string>
#include "UIElement.h"

// Class that represents a text to render to video in 2D
class TextBox : public UIElement
{
	public:
		TextBox();
		~TextBox();

	public:

		void DrawControl(Draw2D* G) override;
};

