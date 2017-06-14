#pragma once

#include <GL\glew.h>
#include <map>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "GlyphInfo.h"

typedef FT_ULong Char;

//Enumerazione che permette di individuare
enum FontAtlas_Descriptor
{
	FontAtlas_Descriptor_PersonalStandard
};

class SpriteFont;

//Classe che rappresenta un font
class Font
{
	friend SpriteFont;

	static FT_Library freeType; //Libreria di FreeType
	static int maxTextureSize; //Dimensione in pixel massima supporata dal dispositivo utilizzato

	GLuint idTexture; //ID della texture secondo OpenGL contenente l'atlas dei caratteri
	std::map<Char, GlyphInfo> charactersMap; //Abbina a ogni carattere il corrispettivo descrittore
	size_t quality; //Qualità scelta per il font (usato solo se .ttf)


public:
	Font();
	~Font();


	//METODI STATICI:
public:

	//Consente di convertire una stringa con caratteri ascii in caratteri unicode
	//@param[in] C - Caratteri da convertire
	//@return Sequenza di caratteri unicode
	//@NOTA è a carico dell'utente eliminare l'array ritornato
	static const Char* ToChar(const char* C);

private:

	//Consente di inizializzare la libreria Free Type e le variabili
	//statiche della classe
	//@friend Metodo creato per essere accesso solo dalla lcasse "SpriteFont"
	static void Inizialize();

	//METODI:
public:

	//Consente di caricare un file .ttf contenente le informazioni riguardo ai set di catatteri
	//@param[in] TTFPath - Path del file .ttf
	//@param[in] Quality - Coefficiente rappresentante la qualità (più è alta più è di qualità)
	//@return True se il caricamento ha avuto successo, Flase altrimenti
	//	Il caricamento ha successo se:
	//		• La libreria FreeType non da errori
	//		• I caratteri del font stanno in una texture
	bool Load(const char* TTFPath, const size_t Quality);

	//Consente di caricare una texture atlas di caratteri da usare come font
	//@param[in] AtlasPath - Path dell'immagine dell'atlas dei caratteri
	//@param[in] DescrittorePath - Path del descrittore dell'atlas (indica la posizione dei caratteri nell'immagine)
	//@param[in] Type - Indica il formato del descrittore
	void Load(const char* AtlasPath, const char* DescrittorePath, FontAtlas_Descriptor Type);

	//Ottiene l'ID della texture contenente l'atlas dei glifi
	GLuint getIDTexture() const;

	//Ottiene la qualità utilizzata per la realizzazione di questo font (se .ttf)
	int getQuality() const;

	//Ottiene la porzione di texture contenente il carattere indicato
	//Se il carattere non è presente ritorna null
	const GlyphInfo* getGlyphInfo(Char C) const;
};