#pragma once

#include "Shader.h"
#include "Light.h"
#include <vector>

class Model;
class Mesh;
class Material;
class Actor;
class ActorParameters;

//Classe astratta che rappresenta uno shader generico per il rendering di un modello
class ModelShader : public Shader
{
	protected:
		GLuint idVertecesCoords; //ID dell'array delle coordinate dei vertici (deve esserte presente)
		GLuint idVertecesUVs; //ID dell'array con le uv dei vertici (se non presente non settarlo o settarlo a INVALID_BUFFER_ID)
		GLuint idVertecesNormals; //ID dell'array le normali dei vertici (se non presente non settarlo o settarlo a INVALID_BUFFER_ID)

		bool bothSide = false; //Flag che indica se lo shader richiede che vengano renderizzati entrambi i lati dei poligoni

	public:
		ModelShader();
		~ModelShader();


	public:

		//Ottiene l'ID della variabile dello shader che contiene l'array del buffer delle coodinate (x, y, z)
		GLuint getIDVertecesCoords() const; //AGIUNGERE I VARI ID DEGLI ATTRIBUTI DEI VERTICI
		//Ottiene l'ID della variabile dello shader che contiene l'array del buffer delle UV (u, v)
		GLuint getIDVertecesUVs() const;
		//Ottiene l'ID della variabile dello shader che contiene l'array del buffer delle normali (x, y, z)
		GLuint getIDVertecesNormals() const;
		//Ottiene un flag che indica se lo shader richiede che vengano renderizzati entrambi i lati dei poligoni
		bool getBothSide() const;

		//Permette di settare i parametri relativi alle luci, per poter renderizzare i modelli successivi
		//utilizzando quelle luci
		//@param[in] Lights - Luci da considerare nel rendering dei futuri modelli
		virtual void SetSceneLights(const std::vector<Light*>& Lights) abstract;

		//Imposta la luce d'ambiente nella scena pqe i prossimi modelli da renderizzare
		//@NOTA: Si richiede che alla chiamata di questo metodo si sia eseguita l'istruzione:
		//		glUseProgram(ModelShader->GetShaderID());
		virtual void SetAmbientLight(const glm::vec3& L) abstract;

		//Imposta le proprietà necessarie per il materiale indicato
		//@param[in] M - Materiale da impostare
		//@NOTA: Si richiede che alla chiamata di questo metodo si sia eseguita l'istruzione:
		//		glUseProgram(ModelShader->GetShaderID());
		virtual void SetMaterial(const Material* M) abstract;

		//Setta le variabili dello shader relative alla camera
		//@param[in] ViewMatix - Matrice della vista
		//@param[in] ProjectionMatrix - Proiezione del mondo di gioco
		//@NOTA: Si richiede che alla chiamata di questo metodo si sia eseguita l'istruzione:
		//		glUseProgram(ModelShader->GetShaderID());
		virtual void SetCameraParameters(const glm::mat4& ViewMatix, const glm::mat4& ProjectionMatrix) abstract;

		//Permette di settare i parametri dell'oggetto da renderizzare
		//@param[in] P - Parametri per lo shader (può essere null se lo shader non necessita di parametri)
		//@param[in] ModelMatrix - Matrice del modello
		//@NOTA 1: è necessario usare i due metodi SetMaterial() e SetMesh() prima di chiamare questo metodo
		//	E' facoltativo invece chiamare i metodi delle luci SetSceneLights() e SetAmbientLight()
		//@NOTA 2: Si richiede che alla chiamata di questo metodo si sia eseguita l'istruzione:
		//		glUseProgram(ModelShader->GetShaderID());
		virtual void SetObjectParameters(const ActorParameters* P, const glm::mat4& ModelMatrix) abstract;
};

