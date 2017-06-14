#pragma once

#include <vector>


#include "IDCollection.h"
#include "MapIterator.h"

#include "Actor.h"
#include "Camera.h"
#include "Light.h"
#include "Skybox.h"

#include "UI.h"

#include "ItemScene.h"

#include "UpdateParameters.h"
#include "RenderingEngineInfo.h"

class Engine;

//Classe che rappresenta una scena del gioco
class Scene
{
	//Attori presenti all'interno della scena 
	//Vettore ordinato secondo l'ordine di rendering ordinamento
	//Shader
	//Texture
	//Proprietà del materiale
	//Mesh (Verteces buffers)
	std::vector<Actor*> actors;
	unsigned int addedActors; //Numero di attori aggiunti dalla scorsa operazione di sorting
	std::map<unsigned int, Light*> lights; //Luci presenti nella scena
	std::map<unsigned int, Camera*> cameras; //Camere utilizzate per il rendering
	UI ui;


	IDCollection<ItemScene*> items; //Qualsiasi Item contenuto nella scena: camere, attori, luci, ...

	Engine* engine; //Engine di appartenza della scena

	const Skybox* skybox; //Skybox della scena

	protected:

		glm::vec3 ambientLight; //Ambient light della scena, usato negli shader che supportano l'illuminazione

	public:
		Scene();
		~Scene();

	public:

		//Inizializza la scena
		void Inizialize(Engine* E);

		//Consente di aggiornare la scena
		//@param[in] SceneUpdateParameters - Parametri per la scena
		void Update(const UpdateParameters& SceneUpdateParameters);

		//Metodo da chiamare quando la dinestra di gioco viene ridimensionata
		void OnScreenResize(size_t NewWidth, size_t NewHeight);

		//Ottiene gli attori contenuti nella scena
		const std::vector<Actor*>* getActors();

		//Ottiene le camere
		MapIterator<unsigned int, Camera*> getCameras();

		//Ottiene le luci presenti nella scena
		MapIterator<unsigned int, Light*> getLigths();

		//Ottiene lo skybox della scna (se è nullo non è presente nella scena)
		const Skybox* getSkyBox();

		//Rimuove l'Item con ID indicato
		//NOTA: metodo chiamato automaticamente da ItemScene.RemoveFromScene()
		void RemoveItem(unsigned int ID);

		//Ottiene l'ultimo stato dell'input occorso durante l'ultimo update della scena
		InputState* getLastInputState();

		//Permette di ordinare l'array degli attori per ottimizzare il tempo di rendering
		void SortActors();

		//Ottiene la luce d'ambiente della scena, usato negli shader che supportano l'illuminazione
		glm::vec3 getAmbientLight() const;

		//Ottiene l'UI della scena
		UI& getUI();

	protected:


		//--- METODI DA EREDITARE

		//Permette di inizializzare la propria scena
		virtual void InizializeScene() abstract;

		//Consente di aggiornare la scena
		virtual void UpdateScene(const UpdateParameters& SceneUpdateParameters) abstract;

		//--- METODI UTILIZZABILI DALLA SCENA DERIVATA

		//Ottiene un nuovo oggetto Camera per la scena
		//@param[in] ModeOffset - Modalità desiderata di misura per l'offset della camera
		//@param[in] X - Modalità desiderata di misura per la dimensione delal camera
		//@param[in] Y - Modalità desiderata di misura per la dimensione delal camera
		//@param[in] ModeSize - Modalità desiderata di misura per la dimensione della camera
		//@param[in] Width - Lunghezza della camera rispetto alla finestra (utilizza la modalità indicata precedentemente)
		//@param[in] Height - Altezza della camera rispetto alla finestra (utilizza la modalità indicata precedentemente)
		//@return Camera creata
		Camera* InsertNewCamera(MeasureMode ModeOffset, float X, float Y, MeasureMode ModeSize, float Width, float Height);

		//Inserisce un nuovo attore per la scena
		//@param[in] Attore da aggiungenre; non null
		void InsertNewActor(Actor* A);

		//Inserisce una nuova luce per la scena
		//@return Luce creata
		Light* InsertNewLight();

		//Imposta/inserisce un nuovo Skybox, può essere nullo
		void InsertSkybox(const Skybox* Skybox);

		//Permette di terminare l'engine
		void Terminate();

		//@return Informazionu sull'operato dell'engine
		const RenderingEngineInfo& getRenderingEngineInfo();

	private:
		

		//Ottiene l'indice di posizione nell'array dell'attore
		//@param[in] A - Attore desiderato
		//@return indice in "actors" se non trovato o l'argomento è null ritorna -1
		int IndexOfActor(const Actor* A);
		//Ottiene l'indice di posizione nell'array dell'attore
		//@param[in] ID - ID dell'attore
		//@return indice in "actors" se non trovato -1
		int IndexOfActor(unsigned int ID);

		//Ottiene l'attore con l'id indicato
		//@param[in] ID - ID dell'attore desiderato
		//@return Attore desiderato o null se non presente
		Actor* GetActor(unsigned int ID);

		
};