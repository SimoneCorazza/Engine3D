#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

class Mesh;
class TextureCube;

// Class representing a generic skybox
class Skybox
{
	// Mesh of the skybox
	const Mesh* mesh;

	// Cubic texture for the skybox
	const TextureCube* textureCube;

	// Size of the skybox with respect to the mesh
	glm::vec3 scale;

	public:
		// Instance a skybox
		Skybox(const Mesh* Mesh, const TextureCube* TextureCube);

		~Skybox();

	public:

		// Set the texture cube map for the skybox
		void setTextureCube(const TextureCube* T);

		// Gets the cube map for the skybox
		const TextureCube* getTextureCube() const;

		// Change the size of the skybox
		void setScale(const glm::vec3& S);

		// Gets the vector of magnifying the skybox with respect to the selected model
		const glm::vec3& getScale() const;

		// Get the skybox mesh
		const Mesh* getMesh() const;

		// Gets the transformation matrix of the skybox
		// @param[in] CameraPos - Location of the camera (to be able to center the skybox on it)
		const glm::mat4 getMatrix(const glm::vec3& CameraPos) const;
};