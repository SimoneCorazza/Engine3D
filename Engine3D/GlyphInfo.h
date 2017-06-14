#pragma once

#include "RectangleF.h"

//Classe che consente di memorizzare tutte le varie informazioni riguardo un glifo
class GlyphInfo
{
	//ATTRIBUTI:
public:
	RectangleF areaUV; //Area occupata dal carattere nella texture

	int width; //Dimensione X della texture
	int height; //Dimensione Y della texture
	int bitmapTop;
	int bitmapLeft;


	//COSTRUTTORI:
public:
	GlyphInfo();
	~GlyphInfo();


	//METODI:
public:


};