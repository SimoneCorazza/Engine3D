#pragma once


#include <glm\glm.hpp>
#include <GL\glew.h>
#include <vector>

#include "ItemScene.h"
#include "Point2.h"
#include "PostProcessEffect.h"

class PostProcessShaderParams;
class PostProcessShader;

//Enumerazione per indicare come vine interpretata una misura
enum MeasureMode
{
	MeasureMode_Rate, //Indica che la misura sarà in percentuale
	MeasureMode_Constant, //Indica che la misura sarà espressa in cifre esatte e non dovrà cambiare
};

//Enumerazione per indicare se è presente il face culling e se sì la modalità
//i valori assunti se è abilitato sono coincidenti con quelli de OpenGL
enum FaceCulling : int
{
	FaceCulling_Disabled = 0, //Face culling disabilitato
	FaceCulling_Front = GL_FRONT, //Face culling abilitato e settato sul fronte della faccia
	FaceCulling_Back = GL_BACK, //Face culling abilitato e settato sul retro della faccia
	FaceCulling_FrontAndBack = GL_FRONT_AND_BACK,  //Face culling abilitato e settato sul fronte della faccia
};


//Classe che rappresenta la porzione di mondo visualizzato
class Camera : public ItemScene
{
	//Visuale:
	glm::vec3 direction; //Direzione della camera
	glm::vec3 position; //Posizione della camera
	float horizontalAngle; //Angolo orizzontale
	float verticalAngle; //Angolo verticale

	//Limiti della visuale della camera:
	float maxHorizontalAngle; //Angolo massimo (verso destra) possibile per la camera
	float minHorizontalAngle;  //Angolo minimo (verso sinistra) possibile per la camera
	float maxVerticalAngle; //Angolo massimo (verso l'alto) possibile per la camera
	float minVerticalAngle;  //Angolo minimo (verso il basso) possibile per la camera

	// Initial Field of View
	#define INITIAL_FOV 45.0f
	
	float fovY; //Fov delal camera
	float aspectRatio; //Ratio attuale della camera
	float zNear; //Minima distanza a cui gli oggetti vengono renderizzati
	float zFar; //Massima distanza a cui gli oggetti vengono renderizzati

	float speed;
	float mouseSpeed;

	float coefficienteVelocitaCamera;

	glm::mat4 viewMatrix; //Matrice della vista ottenuta dall'utente tramite le periferiche di input
	glm::mat4 cameraMatrix; //Matrice della camera ottenuta moltiplicando nell'ordine: la matrice della proiezione con quella della vista
	glm::mat4 projectionMatrix; //Matrice della proiezione settata dall'utente

	bool focused; //Indica se la camera è selezionata e pronta per l'input
	bool frustumCulling; //Indica se per la camera è abilitato il frustum culling per gli attori da renderizzare
	FaceCulling faceCulling; //Indica il face culling della camera

	Point2 offset; //Offset della camera in pixel
	Point2 size; //Dimensione della camera in pixel

	MeasureMode modeOffset; //Modalità di trattare la misura dell'offset
	glm::vec2 measureOffset; //Misura dell'offset della camera secondo la modalità presecelta (pixel, percentuale, ...)
	MeasureMode modeSize; //Modalita di trattare la misura della size
	glm::vec2 measureSize;  //Misura della dimensione della camera secondo la modalità presecelta (pixel, percentuale, ...)

	//-- POST PROCESS EFFECTS

	GLuint idFrameBuffer; //Framebuffer della camera
	//Ids della texture collegata al frame buffer, dove viene inserito il risultato dell'operazione del rendering,
	//sono due per poter scambiarsi a turno per poter applicari più effetti post-process
	GLuint idRenderTextures[2];
	GLuint idDepthTexture; //Id della texture collegata al frame buffer, dove viene inserità la profondità

	GLuint depthRenderBuffer; //Depth buffer inserito nel framebuffer

	unsigned int idPostProcessEffectsCounter; //Contatore per la generazione degli id degli effetti prost process
	std::vector<PostProcessEffect*> postProcessEffects; //Effetti post rendering della camera

	public:
		//Istanzia una camra
		//@param[in] ID - ID della camera
		//@param[in] Scene - Scena contenente la camera
		//@param[in] ModeOffset - Modalità desiderata di misura per l'offset della camera
		//@param[in] X - Modalità desiderata di misura per la dimensione delal camera
		//@param[in] Y - Modalità desiderata di misura per la dimensione delal camera
		//@param[in] ModeSize - Modalità desiderata di misura per la dimensione della camera
		//@param[in] Width - Lunghezza della camera rispetto alla finestra (utilizza la modalità indicata precedentemente)
		//@param[in] Height - Altezza della camera rispetto alla finestra (utilizza la modalità indicata precedentemente)
		//Camera(unsigned int ID, Scene* Scene, MeasureMode ModeOffset, float X, float Y, MeasureMode ModeSize, float Width, float Height);

		//Istanzia una camra
		//@param[in] ModeOffset - Modalità desiderata di misura per l'offset della camera
		//@param[in] X - Modalità desiderata di misura per la dimensione delal camera
		//@param[in] Y - Modalità desiderata di misura per la dimensione delal camera
		//@param[in] ModeSize - Modalità desiderata di misura per la dimensione della camera
		//@param[in] Width - Lunghezza della camera rispetto alla finestra (utilizza la modalità indicata precedentemente)
		//@param[in] Height - Altezza della camera rispetto alla finestra (utilizza la modalità indicata precedentemente)
		Camera(MeasureMode ModeOffset, float X, float Y, MeasureMode ModeSize, float Width, float Height);
		~Camera();


	public:


		//Permette di aggiornare l'interfaccia della camera
		//NOTA: riservato alla classe SCENE
		void Update(float ElapsedTime);

		//Metodo che permette di aggiornare la camera al cambiamento di dimensioni della finestra di gioco
		//NOTA: riservato alla classe SCENE
		void OnScreenReSize(size_t NewWidth, size_t NewHeight);

		//Consente di abilitare la camera agli input
		void Focus();
		//Consente di disabilitare la camera agli input
		void Unfocus();
		//Consente di invertire lo stato di focus della camera
		void SwitchFocus();

		//-- Effetti post-processing

		//Aggiunge un'effetto post process
		//@param[in] S - Shader da usare come effeto
		//@param[in] P - Parametri per lo shader dell'effetto (possono esse NULL, se lo shader lo supporta)
		//@return Effetto risultate
		PostProcessEffect* AddPostProcessEffect(const PostProcessShader* S, PostProcessShaderParams* P);

		//Permette di rimuovere un'effetto post process dall'elenco
		void RemovePostProcessEffect(int ID);

		//Ottiene gli effetti post process delal camera
		const std::vector<PostProcessEffect*>* getPostProcessEffects() const;

		//Cambia la textrue dove andare a renderizzare il frame buffer
		//@param[in] Index - Indica la texture su cui renderizzare: 0 o 1
		void changePostProcessRenderTexture(int Index) const;

		//GET e SET

		//Imposta la matrice della proiezione
		void setProjectionMatrix(const float& FovY, const float& AspectRatio, const float& ZNear, const float& ZFar);

		//Ottiene la matrice della camera ottunuta dal prodotto della matrice della proiezione con quella della vista
		const glm::mat4& getCameraMatrix() const;

		//Ottiene la matrice della proiezione della camera
		const glm::mat4& getProjectionMatrix() const;

		//Ottiene la matrice della vista della camera
		const glm::mat4& getViewMatrix() const;

		//Ottiene la posizione dell'angolo della camera nella finestra
		const Point2& getOffset() const;
		//Ottiene la dimensione della camera nella finestra
		const Point2& getSize() const;

		//Ottiene un flag che indica se la camera è abilitata (riceve gli input)
		const bool& isFocus() const;

		//Imposta un flag che indica se la camera abilita il frustum culling
		void setFrustumCulling(const bool& B);
		//Ottiene un flag che indica se la camera abilita il frustum culling
		const bool& getFrustumCulling() const;

		//Ottiene il face culling della camera
		const FaceCulling& getFaceCulling() const;
		//Imposta il face culling della camera
		void setFaceCulling(const FaceCulling& F);

		//Imposta la posizione della camera
		void setPosition(const glm::vec3& P);
		//Ottiene la posizione della camera
		const glm::vec3& getPosition() const;

		//Frame buffer:

		//Ottiene l'id del framebuffer della camera
		GLuint getFrameBufferID() const;
		//Ottiene l'id della texture del frame renderizzato
		//@param[in] Index - Indice della texture del frame attuale desiderato (0 o 1)
		GLuint getRenderedTextureID(int Index) const;
		//Ottiene l'id della texture della profondità della scena
		GLuint getDepthTextureID() const;

		//Limiti movimento visuale:

		//Imposta l'angolo massimo (verso destra) possibile per la camera
		//il valore deve essere > 0 o = 0 per non dare limiti
		//PI / 2 = guarda verso destra
		void setMaxHorizontalAngle(float A);
		//Imposta angolo minimo (verso sinistra) possibile per la camera
		//il valore deve essere < 0 o = 0 per non dare limiti
		//PI / 2 = guarda verso sinistra
		void setMinHorizontalAngle(float A);
		//Imposta angolo massimo (verso l'alto) possibile per la camera
		//il valore deve essere > 0 o = 0 per non dare limiti
		//PI / 2 = guarda verso l'alto
		void setMaxVerticalAngle(float A);
		//Imposta angolo minimo (verso il basso) possibile per la camera
		//il valore deve essere < 0 o = 0 per non dare limiti
		//PI / 2 = guarda verso il basso
		void setMinVerticalAngle(float A);

		//Ottiene l'angolo massimo (verso destra) possibile per la camera
		float getMaxHorizontalAngle();
		//Ottiene angolo minimo (verso sinistra) possibile per la camera
		float getMinHorizontalAngle();
		//Ottiene angolo massimo (verso l'alto) possibile per la camera
		float getMaxVerticalAngle();
		//Ottiene angolo minimo (verso il basso) possibile per la camera
		float getMinVerticalAngle();

	private:

		//Ottiene la posizione occupata dall'effetto con id indicato (se non presente ritorna -1)
		int FindPostProcessEffect(int ID);

		//Consente di trasformare una misura dalla sua modalità in pixel
		//@param[in] Mode - Modalità di misura
		//@param[in] Measure - Misura da trasformare
		//@param[in] WindowSize - Dimensione delal finestra in pixel
		Point2 static TransformToPixel(const MeasureMode& Mode, const glm::vec2& Measure, const Point2& WindowSize);

		//Permette di posizionare il cursore al centro della camera
		void CenterCursor();

		//Consente di aggiornare il ratio della projection matrix (e conseguentemente alla camera matrix)
		//in base alla dimensione dello schermo
		void UpdateRatio();

		//Consente di aggiornare il frame buffer della camera
		void UpdateFrameBuffer();
};

