#include "UIElement.h"



UIElement::UIElement()
{
	font = nullptr;
	textColor = glm::vec4(0, 0, 0, 1);
}


UIElement::~UIElement()
{
}

void UIElement::setArea(const Rectangle & A)
{
	area = A;
}

const Rectangle & UIElement::getArea()
{
	return area;
}

void UIElement::setText(const std::string & T)
{
	text = T;
}

const std::string& UIElement::getText() const
{
	return text;
}

void UIElement::setVerticalTextAllign(VerticalTextAllign A)
{
	verticalAllign = A;
}

VerticalTextAllign UIElement::getVerticalTextAllign() const
{
	return verticalAllign;
}

void UIElement::setHorizontalTextAllign(HorizontalTextAllign A)
{
	horizontalAllign = A;
}

HorizontalTextAllign UIElement::getHorizontalTextAllign() const
{
	return horizontalAllign;
}

void UIElement::setFont(const Font * F)
{
	font = F;
}

const Font * UIElement::getFont()
{
	return font;
}

void UIElement::setTextColor(const glm::vec4 & C)
{
	textColor = C;
}

const glm::vec4 & UIElement::getTextColor()
{
	return textColor;
}
