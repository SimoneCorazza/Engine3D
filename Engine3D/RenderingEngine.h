#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>

#include "PostProcess_Final.h"
#include "SkyboxShader.h"
#include "CheckTable.h"
#include "ModelShader.h"
#include "Draw2D.h"

#include "RenderingEngineInfo.h"

class Scene;
class Skybox;
class Camera;
struct Rectangle;

//Classe che gestisce il rendering dell'engine
class RenderingEngine
{
	glm::vec4 backgroundColor; //Clear color

	//-- SKYBOX

	SkyboxShader skyboxShader;

	//-- POST PROCESS

	PostProcess_Final postProcess_final; //Effetto post process per il passaggio finale dal frame buffer allo schermo

	//--- INTERFACE

	Draw2D draw2d; //Classe per renderizzare i vari elementi delle UI

	//-- DEFAULT DATA

	//ID del buffer contenente un quadrato di lato 2, posizionato sull'origine
	//il quadrato è formato da due triangoli separati
	//Usato per esempio dal vertex shader per gli effetti post-render
	static GLuint idBuffUnitQuad;

	//-- SUPPORT STRUCTURE
	//Strutture di supporto per il rendering
	
	//-- INFO SULL'ENGINE ---

	RenderingEngineInfo info;


	public:
		RenderingEngine();
		~RenderingEngine();


	public:

		//Permette di inizializzare il rendering engine
		void Inizialize();

		//Metodo per indicare che la finestra è stata ridimensionata
		//@param[in] Width - Nuova lunghezza della finestra in pixel
		//@param[in] Height - Nuova altezza della finestra in pixel
		void WindowResized(int Width, int Height);

		//Imposta il colore di background
		void setBackgroundColor(const glm::vec4& C);

		//Consente di renderizzare la scena
		void RenderScene(Scene& S);
		
		//@return Informazionu sull'operato dell'engine
		const RenderingEngineInfo& getRenderingEngineInfo() const;

		//Ottiene l'id del buffer contenente un quadrato di lato 2, posizionato sull'origine
		//il quadrato è formato da due triangoli separati
		static GLuint getIDBuffUnitQuad();

	private:

		//Renderizza lo skybox della scena
		void RenderSkybox(const Skybox* S, const Camera& C);

		//Applica gli effetti post render alla camera e disegna il frame risultate a schermo
		//@NOTA: Si assume:
		//	•che la scena per la data camera sia già stata renderizzata sulla texture con ID 0
		//	•che sia ancora selezionato la FBO della camera
		//@NOTA FINALE: Questo metodo è stato testato solo subito dopo il rendering della data camera
		//@param[in] C - Camera dalla quale renderizzare gli effetti post-process
		//@param[in] Portion - Porzione a schermo riservata alla camera in pixel
		void ApplayPostRenderEffects(const Camera& C, const Rectangle& Portion);

		//Permette di renderizzare la scena indicata
		//@param[in] S - Scena di cui disegnare l'interfaccia
		void RenderUI(Scene& S);

		//Consente di abilitare le variabili/attributi per i buffer della mesh
		//@param[in] S - Shader su cui settare i buffer
		void EnableArraysShader(const ModelShader* S);

		//Permette di settare gli attributi della mesh nello shader quali: vertici, uv e normali
		//(se richiesti dallo shader)
		//@param[in] S - Shader a cui settare i buffer della mesh
		//@param[in] M - Mesh da settare nello sahder
		void SetArraysShader(const ModelShader* S, const Mesh* M);

		//Consente di disabilitare le variabili/attributi per i buffer della mesh
		//@param[in] S - Shader da disabilitare
		void DisableArrayShader(const ModelShader* S);
};

