#pragma once

#include <glm\glm.hpp>


class ModelShader;
class Texture2D;

//Classe che racchiude l'informazioni del materiale
class Material
{
	ModelShader* shader; //Shader da utilizzare per il rendering del modello
	const Texture2D* texture; //Texture del materiale

	//Propriet� per la luce:

	glm::vec3 ambient; //Luce trasmessa dall'ambiente (dovuta a riflessioni di luce da altri oggetti)
	glm::vec3 diffuse; //For the diffuse reflection: for a black surface is 0 for a white surface it is 1
	glm::vec3 specular; //For the specular reflection
	float shininess; //Lucentezza del materiale, maggiore � pi� l'oggetto risplender�

	public:
		Material();
		
		Material(ModelShader* Shader, const Texture2D* Texture);
		~Material();

	public:

		//Ottiene lo shader che renderizza il modello
		ModelShader* getShader() const;
		//Ottiene la texture del modello
		const Texture2D* getTexture() const;

		//Imposta la luce trasmessa dall'ambiente (dovuta a riflessioni di luce da altri oggetti) che irradia il modello
		void setAmbient(const glm::vec3& V);
		//Ottiene la luce trasmessa dall'ambiente (dovuta a riflessioni di luce da altri oggetti) che irradia il modello 
		const glm::vec3& getAmbient() const;
		
		//Imposta il parametro per la riflessione diffusa (diffuse reflection) per una superficie nera � 0 per una bianca � 1
		void setDiffuse(const glm::vec3& V);
		//Ottiene il parametro per la riflessione diffusa (diffuse reflection) per una superficie nera � 0 per una bianca � 1
		const glm::vec3& getDiffuse() const;

		//Imposta il parametro per la riflesione speculare
		void setSpecular(const glm::vec3& V);
		//Ottiene il parametro per la riflesione speculare
		const glm::vec3& getSpecular() const;

		//Imposta la lucentezza del materiale pi� � pi� risplende
		void setShininess(float S);
		//Ottiene la lucentezza del materiale pi� � pi� risplende
		float getShininess() const;

	private:

		//Inizializza i parametri del materiale relativi alla luce
		inline void DefaultLightSettings();
};

