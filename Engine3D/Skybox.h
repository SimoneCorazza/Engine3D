#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

class Mesh;
class TextureCube;

// Class representing a generic skybox
class Skybox
{
	const Mesh* mesh; // Mesh of the skybox
	const TextureCube* textureCube; // Cubic texture for the skybox
	glm::vec3 scale; // Size of the skybox with respect to the mesh

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
		// @param [in] CameraPos - Location of the room (to be able to center the skybox on it)
		const glm::mat4 getMatrix(const glm::vec3& CameraPos) const;
};

/*
#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

class Model;

// Class representing a generic skybox
class Skybox
{
const Model* model; // Model of the skybox containing the mesh and the material for it
glm::vec3 scale; // Size of the model compared to the original one

public:
// Instance a skybox
Skybox(const Model* model);

~Skybox();

public:

// Change the size of the skybox
void setScale(const glm::vec3& S);

// Gets the vector of magnifying the skybox with respect to the selected model
const glm::vec3& getScale() const;

// Gets the model of the skybox
const Model* getModel() const;

// Gets the transformation matrix of the skybox
// @param [in] CameraPos - Location of the room (to be able to center the skybox on it)
const glm::mat4 getMatrix(const glm::vec3& CameraPos) const;
};
*/