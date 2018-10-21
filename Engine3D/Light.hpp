#pragma once

/*
Reference pages:
General: https://en.m.wikibooks.org/wiki/GLSL_Programming/GLUT/Diffuse_Reflection
Attenuation: https://developer.valvesoftware.com/wiki/Constant-Linear-Quadratic_Falloff
*/

#include <glm\glm.hpp>

#include "ItemScene.hpp"

class Scene;

// Class for a light that can be placed on a scene 
class Light : public ItemScene
{
	public:

		// Indicates if the light is active or not
		bool state;

		// if w = 0 is a directional light and the xyz components indicate its direction (directional light)
		// if w! = 0 is a point or spot light
		glm::vec4 position;
		glm::vec4 diffuse; // Color and strength of light (referred to as I_diffuse in the tutorial)
		glm::vec4 specular;
		float constantAttenuation; // Constant attenuation [0, 1]
		float linearAttenuation;  // Linear attenuation [0, 1]
		float quadraticAttenuation;  // Quadratic attenuation [0, 1]
		float spotCutoff; // Variable for spotlights: angle of cut in degrees (if it is <= 90 the light is considered a spotligth)
		float spotExponent; // Variable for spotlights: indicates how much light decays between the center and the edge
		glm::vec3 spotDirection; // Variable for spotlights: direction of the spotlight


	public:
		Light();
		~Light();


	public:

		// Indicates if it is a directional light
		bool isDirectional();

		// Gets the position of light in the game world
		const glm::vec3& getPosition();

		// Gets the reach of light
		float getClippingRadius();
};

