#pragma once

#include <glm\glm.hpp>


class ModelShader;
class Texture2D;

// Class that contains the information of the material
class Material
{
	// Shader to use for model rendering
	ModelShader* shader;

	// Texture of the material
	const Texture2D* texture;

	// Properties for light:

	// Light transmitted from the environment (due to reflections of light from other objects)
	glm::vec3 ambient;

	// For the diffuse reflection: for a black surface
	glm::vec3 diffuse;

	// For the specular reflection
	glm::vec3 specular;

	// Shine of the material, the greater the object the more it will shine
	float shininess;

	public:
		Material();
		
		Material(ModelShader* Shader, const Texture2D* Texture);
		~Material();

	public:

		// Gets the shader that renders the model
		ModelShader* getShader() const;
		// Gets the texture of the model
		const Texture2D* getTexture() const;

		// Sets the light transmitted by the environment (due to reflections of light from other objects) that radiates the model
		void setAmbient(const glm::vec3& V);
		// Gets the light transmitted by the environment (due to reflections of light from other objects) that radiates the model
		const glm::vec3& getAmbient() const;
		
		// Set the parameter for diffuse reflection for a black surface is 0 for a white surface is 1
		void setDiffuse(const glm::vec3& V);
		// Gets the parameter for diffuse reflection for a black surface is 0 for a white surface is 1
		const glm::vec3& getDiffuse() const;

		// Set the parameter for the specular reflection
		void setSpecular(const glm::vec3& V);
		// Gets the parameter for the specular reflection
		const glm::vec3& getSpecular() const;

		// Set the shine of the material
		void setShininess(float S);
		// It gets the luster of the material
		float getShininess() const;

	private:

		// Initializes the parameters of the light-related material
		inline void DefaultLightSettings();
};

