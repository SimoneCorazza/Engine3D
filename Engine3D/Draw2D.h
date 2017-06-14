#pragma once

#include "SpriteFont.h"
#include "Point2.h"

//Classe utilizzata per il disegno in 2D dell'interfaccia
class Draw2D
{
	Point2 monitorMM; //Dimensione del monitor principale in millimetri
	Point2 resolution; //Risoluzione correntemente utilizzata per il monitor
	Point2 windowSizeMM; //Dimensione della finestra in millimetri
	glm::mat4 matrix; //Matrice 2D per il calcolo dei vertici

	SpriteFont sf; //Classe usata per il rendering dei caratteri



	public:
		Draw2D();
		~Draw2D();

	public:

		//Inizializza la classe
		void Inizialize();

		//Imposta la dimensione dello schermo
		//@param[in] Width - Dimensione (X) della finestra in pixel
		//@param[in] Height - Dimensione (Y) della finestra in pixel
		void SetWindowSize(float Width, float Height);

		//Disegna la stringa con il font scelto
		//@param[in] String - Stringa da renderizzare
		//@param[in] Font - Font da utilizzare
		//@param[in] Location - Posizione dalla quale partire a disegnare il font in millimetri
		//@param[in] Height - Altezza dei caratteri in millimetri
		//@param[in] Color - Colore da utilizzare per il font
		//@NOTA Se un carattere non è presente nel font viene ignorato
		void DrawText(const char* String, const Font* Font, const Point2& Location, size_t Height, const glm::vec4& Color);
};

