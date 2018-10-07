#pragma once

#include <glm\glm.hpp>


class ModelShader;
class Texture2D;

// Class that contains the information of the material
class Material
{
	ModelShader* shader; // Shader to use for model rendering
	const Texture2D* texture; // Texture of the material

	// Properties for light:

	glm::vec3 ambient; // Light transmitted from the environment (due to reflections of light from other objects)
	glm::vec3 diffuse; // For the diffuse reflection: for a black surface
	glm::vec3 specular; // For the specular reflection
	float shininess; // Shine of the material, the greater the object the more it will shine

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
		
		// Set the parameter for diffuse reflection (diffuse reflection) for a black surface is 0 for a white surface is 1
		void setDiffuse(const glm::vec3& V);
		// Gets the parameter for diffuse reflection (diffuse reflection) for a black surface is 0 for a white surface is 1
		const glm::vec3& getDiffuse() const;

		// Set the parameter for the specular reflection
		void setSpecular(const glm::vec3& V);
		// Gets the parameter for the specular reflection
		const glm::vec3& getSpecular() const;

		// Set the shine of the material the more it is glowing
		void setShininess(float S);
		// It gets the luster of the material the more it is glowing
		float getShininess() const;

	private:

		// Initializes the parameters of the light-related material
		inline void DefaultLightSettings();
};

