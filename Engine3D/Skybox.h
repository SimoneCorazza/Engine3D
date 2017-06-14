#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

class Mesh;
class TextureCube;

//Classe che rappresenta uno skybox generico
class Skybox
{
	const Mesh* mesh; //Mesh dello skybox
	const TextureCube* textureCube; //Texture cubica per lo skybox
	glm::vec3 scale; //Dimensione dello skybox rispetto alla mesh

	public:
		//Istanza uno skybox
		Skybox(const Mesh* Mesh, const TextureCube* TextureCube);

		~Skybox();

	public:

		//Imposta la texture cube map per lo skybox
		void setTextureCube(const TextureCube* T);

		//Ottiene la cube map per lo skybox
		const TextureCube* getTextureCube() const;

		//Modifica la dimensione dello skybox
		void setScale(const glm::vec3& S);

		//Ottiene il vettore di ingrandimento dello skybox rispetto al modello selezionato
		const glm::vec3& getScale() const;

		//Ottiene la mesh dello skybox
		const Mesh* getMesh() const;

		//Ottiene la matrice di transformazione dello skybox
		//@param[in] CameraPos - Posizione della camera (per poter centrare lo skybox su di essa)
		const glm::mat4 getMatrix(const glm::vec3& CameraPos) const;
};

/*
#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

class Model;

//Classe che rappresenta uno skybox generico
class Skybox
{
const Model* model; //Modello dello skybox contenente la mesh e il materiale per esso
glm::vec3 scale; //Dimensione del modello rispetto a quello originale

public:
//Istanza uno skybox
Skybox(const Model* model);

~Skybox();

public:

//Modifica la dimensione dello skybox
void setScale(const glm::vec3& S);

//Ottiene il vettore di ingrandimento dello skybox rispetto al modello selezionato
const glm::vec3& getScale() const;

//Ottiene il modello dello skybox
const Model* getModel() const;

//Ottiene la matrice di transformazione dello skybox
//@param[in] CameraPos - Posizione della camera (per poter centrare lo skybox su di essa)
const glm::mat4 getMatrix(const glm::vec3& CameraPos) const;
};
*/