#pragma once

#include "Draw2D.h"

#include "Rectangle.h"



// Alignment of the text on the vertical axis
enum VerticalTextAllign
{
	VTA_Top,
	VTA_Middle,
	VTA_Bottom
};

// Alignment of the text on the horizontal axis
enum HorizontalTextAllign
{
	HTA_Left,
	HTA_Middle,
	HTA_Right,
};


// Class representing an element of the UI
class UIElement
{
	Rectangle area; // Area occupied by video from the element in millimeters

	std::string text; // Text from the element
	VerticalTextAllign verticalAllign; // Vertical alignment of the text
	HorizontalTextAllign horizontalAllign; // Horizontal alignment of the text
	const Font* font; // Font for the text
	glm::vec4 textColor; // Text color

	public:
		UIElement();
		~UIElement();

	public:

		// It allows you to draw the control
		// @param [in] G - Graphic element for drawing in control
		virtual void DrawControl(Draw2D* G) abstract;

		// Set the area occupied by the video in mm
		void setArea(const Rectangle& A);
		// Gets the area occupied by video from the element in millimeters
		const Rectangle& getArea();

		// Set the text to be rendered
		void setText(const std::string& T);
		// Gets the contents of the attaule text
		const std::string& getText() const;

		// Set the vertical alignment of the text
		void setVerticalTextAllign(VerticalTextAllign A);
		// Gets the alignment of vertical text
		VerticalTextAllign getVerticalTextAllign() const;

		// Set the horizontal alignment of the text
		void setHorizontalTextAllign(HorizontalTextAllign A);
		// Gets the alignment of horizontal text
		HorizontalTextAllign getHorizontalTextAllign() const;

		// Sets the font used for the element's text
		void setFont(const Font* F);
		// Gets the font used for the element's text
		// (null if not set)
		const Font* getFont();

		// Sets the color used for the element's text
		void setTextColor(const glm::vec4& C);
		// Gets the color used for the element's text
		const glm::vec4& getTextColor();
};

