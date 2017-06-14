#pragma once

#include <string>
#include "UIElement.h"

//Classe che rappresenta un testo da renderizzare a video in 2D
class TextBox : public UIElement
{
	public:
		TextBox();
		~TextBox();

	public:

		void DrawControl(Draw2D* G) override;
};

