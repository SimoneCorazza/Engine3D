#pragma once

#include <glm\glm.hpp>

#include "Font.h"


//Classe statica che permette di renderizzare a video i font
class SpriteFont
{
	//Buffers:

	static GLuint idBuffVerteces; //Buffer per i vertici
	static GLuint idBuffUV; //Buffer per le coordinate UV

							//Variabili shader:
	static GLuint idShader;

	//Uniform:
	static GLuint idColor;
	static GLuint idSampler;
	static GLuint idMatrix;

	//Attibuti:
	static GLuint idVertexArray;
	static GLuint idUVArray;

	//Dimensioni:
	static float pixelScreenX;
	static float pixelScreenY;

	static float screenX;
	static float screenY;

public:
	SpriteFont();
	~SpriteFont();

public:

	//Consente di inizializzare lo sprite font
	void Inizialize();

	//Imposta la dimensione dello schermo secondo
	//@param[in] PixelScreenX - Dimensione (X) della finestra in pixel
	//@param[in] PixelScreenY - Dimensione (Y) della finestra in pixel
	//@param[in] ScreenX - Dimensione (X) della finestra in unità geometriche scelta (devono corrispondere con quelle della matrice)
	//@param[in] ScreenY - Dimensione (Y) della finestra in unità geometriche scelta (devono corrispondere con quelle della matrice)
	void SetSizes(float PixelScreenX, float PixelScreenY, float ScreenX, float ScreenY);

	//Imposta la matrice per posizionare i vertici dello spritefont
	void SetMatrix(const glm::mat4& M);

	//Permette di iniziare una sequenza di disegni di font
	void Begin();

	//Inoltra la richiesta di disegno della stringa con il font scelto
	//deve essere incluso tra Begin() e End()
	//@param[in] String - Stringa da renderizzare
	//@param[in] Font - Font da utilizzare
	//@param[in] Location - Posizione dalla quale partire a disegnare il font
	//@param[in] Height - Dimensioni dei caretteri desiderata
	//@param[in] Color - Colore da utilizzare per il font
	void RequestDraw(const Char* String, const Font& Font, const glm::vec2& Location, const float& Height, const glm::vec4& Color);

	//Permette di concludere la sequenza di richieste di disegno e di renderizzarle
	void End();

	//Disegna la stringa con il font scelto
	//@param[in] String - Stringa da renderizzare
	//@param[in] Font - Font da utilizzare
	//@param[in] Location - Posizione dalla quale partire a disegnare il font in millimetri
	//@param[in] Height - Altezza dei caratteri in millimetri
	//@param[in] Color - Colore da utilizzare per il font
	//@NOTA Se un carattere non è presente nel font viene ignorato
	void Draw(const Char* String, const Font* Font, const glm::vec2& Location, const float& Height, const glm::vec4& Color);
};

