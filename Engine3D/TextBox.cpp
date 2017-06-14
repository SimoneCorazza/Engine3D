#include "TextBox.h"



TextBox::TextBox()
{
}


TextBox::~TextBox()
{
}

void TextBox::DrawControl(Draw2D* G)
{
	if (getFont() != nullptr)
		G->DrawText(getText().c_str(), getFont(), Point2(getArea().x, getArea().y), getArea().height, getTextColor());
}




