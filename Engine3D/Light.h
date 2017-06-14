#pragma once

/*
Pagine di riferimento:
Generale: https://en.m.wikibooks.org/wiki/GLSL_Programming/GLUT/Diffuse_Reflection
Attenuazione: https://developer.valvesoftware.com/wiki/Constant-Linear-Quadratic_Falloff
*/

#include <glm\glm.hpp>

#include "ItemScene.h"

class Scene;

//Struct che rappresenta una luce
class Light : public ItemScene
{
	public:

		bool state; //Indica se la luce è attiva o meno

		//se w = 0 è una luce direzionale e le componenti xyz ne indicano la direzione (directional light)
		//se w != 0 è una a point o spot light
		glm::vec4 position;
		glm::vec4 diffuse; //Colore e forza della luce (indicato come I_diffuse nel tutorial)
		glm::vec4 specular;
		float constantAttenuation; //Attenuazione costante [0, 1]
		float linearAttenuation;  //Attenuazione lineare  [0, 1]
		float quadraticAttenuation;  //Attenuazione quadratica  [0, 1]
		float spotCutoff; //Variabile per le spotlight: angolo di taglio in gradi (se è <= 90 la luce è considerata una spotligth)
		float spotExponent; //Variabile per le spotlight: indica di quanto la luce decade tra il centro e il bordo [DA VERIFICARE]
		glm::vec3 spotDirection; //Variabile per le spotlight: direzione della spotlight


	public:
		//Light(unsigned int ID, Scene* Scene);
		Light();
		~Light();


	public:

		//Indica se è una luce direzionale
		bool isDirectional();

		//Ottiene la posizione della luce nel mondo di gioco
		const glm::vec3& getPosition();

		//Ottiene la portata della luce
		float getClippingRadius();
};

