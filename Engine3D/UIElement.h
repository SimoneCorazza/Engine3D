#pragma once

#include "Draw2D.h"

#include "Rectangle.h"



//Allineamento del testo sull'asse verticale
enum VerticalTextAllign
{
	VTA_Top,
	VTA_Middle,
	VTA_Bottom
};

//Allineamento del testo sull'asse orizzontale
enum HorizontalTextAllign
{
	HTA_Left,
	HTA_Middle,
	HTA_Right,
};


//Classe che rappresenta un'elemento dell UI
class UIElement
{
	Rectangle area; //Area occupata a video dall'elemento in millimetri

	std::string text; //Testo da dell'elemento
	VerticalTextAllign verticalAllign; //Allineamento verticale del testo
	HorizontalTextAllign horizontalAllign; //Allineamento orizzontale del testo
	const Font* font; //Font per il testo
	glm::vec4 textColor; //Colore del testo

	public:
		UIElement();
		~UIElement();

	public:

		//Permette di disegnare il controllo
		//@param[in] G - Elemento grafico per disegnare in controllo
		virtual void DrawControl(Draw2D* G) abstract;

		//Imposta l'area occupata a video dall'elemento in millimetri
		void setArea(const Rectangle& A);
		//Ottiene l'area occupata a video dall'elemento in millimetri
		const Rectangle& getArea();

		//Setta il testo da renderizzare
		void setText(const std::string& T);
		//Ottiene il contenuto del testo attaule
		const std::string& getText() const;

		//Imposta l'allineamento verticale del testo
		void setVerticalTextAllign(VerticalTextAllign A);
		//Ottiene l'allineamento del testo verticale
		VerticalTextAllign getVerticalTextAllign() const;

		//Imposta l'allineamento orizzontale del testo
		void setHorizontalTextAllign(HorizontalTextAllign A);
		//Ottiene l'allineamento del testo orizzontale
		HorizontalTextAllign getHorizontalTextAllign() const;

		//Imposta il font utilizzato per il testo dell'elemento
		void setFont(const Font* F);
		//Ottiene il font utilizzato per il testo dell'elemento
		//(null se non impostato)
		const Font* getFont();

		//Imposta il colore utilizzato per il testo dell'elemento
		void setTextColor(const glm::vec4& C);
		//Ottiene il colore utilizzato per il testo dell'elemento
		const glm::vec4& getTextColor();
};

