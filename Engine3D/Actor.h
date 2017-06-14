#pragma once

#include "Model.h"
#include "Box.h"

#include <glm\glm.hpp>

#include "ItemScene.h"

class ActorParameters;
class UpdateParameters;

//Classe che rappresenta un oggetto posizionabile nella scena
class Actor : public ItemScene
{
	const Model* model; //Modello dell'attore
	glm::mat4 modelMatrix; //Matrice del modello

	//Informazioni codificate nella matrice:
	glm::vec3 location; //Posizione occupata dall'attore
	glm::vec3 scale; //Streach effettuato al modello (default (1, 1, 1))
	glm::vec3 rotation; //Rotazione del modello sui rispettivi assi


	protected:
		//Parametri dell'attore per lo shader; null se non c'è nessun parametro
		//Eliminazione effettuata dalla classe base Attore
		ActorParameters* param;


	public:
		Actor();
		~Actor();


	public:

		//Ottiene la locazione della matrice
		const glm::vec3& getLocation() const;
		//Ottine il vettore di scala dell'attore
		const glm::vec3& getScale() const;
		//Ottiene la rotazione dell'attore
		const glm::vec3& getRotation() const;

		//Ottiene il modello 3D dell'attore
		const Model* getModel() const;
		//Ottiene la matrice del modello
		const glm::mat4 getModelMatrix() const;
		//Ottiene il Box contenente il modello 3D dell'attore
		Box* getBox() const;


		void setLocation(const glm::vec3& V);
		void setScale(const glm::vec3& V);
		void setRotation(const glm::vec3& V);
		void setLocation(const float& X, const float& Y, const float& Z);
		void setScale(const float& X, const float& Y, const float& Z);
		void setRotation(const float& X, const float& Y, const float& Z);

		void setModel(const Model* M);

		//Consente di Aggiornare l'attore
		//@param[in] P - Parametri per l'attore
		virtual void Update(const UpdateParameters& P);

		//Imposta il para
		//virtual void setActorParameters(ActorParameters* P);
		//Ottiene i parametri dell'attore (per il rendering o altro)
		//Può ritornare anche null
		const ActorParameters* getActorParameters() const;

	private:

		//Consente di ri-calcolare la matrice dell'attore
		void CalculateMatrix();
};

