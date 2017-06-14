#include "Skybox.h"

#include "Mesh.h"
#include "Utility_GLM.h"

#include "DEBUG.h"

Skybox::Skybox(const Mesh* Mesh, const TextureCube* TextureCube)
{
	ASSERT(Mesh != nullptr && TextureCube != nullptr, "Skybox::Skybox(): params can not be null");

	mesh = Mesh;
	scale = glm::vec3(1); //Inizialment ha la dimensione della mesh
	textureCube = TextureCube;
}

Skybox::~Skybox()
{
}

void Skybox::setTextureCube(const TextureCube * T)
{
	textureCube = T;
}

const TextureCube * Skybox::getTextureCube() const
{
	return textureCube;
}

void Skybox::setScale(const glm::vec3 & S)
{
	scale = S;
}

const glm::vec3 & Skybox::getScale() const
{
	return scale;
}

const Mesh* Skybox::getMesh() const
{
	return mesh;
}

const glm::mat4 Skybox::getMatrix(const glm::vec3& CameraPos) const
{
	//Calcolo la matrice dello skybox in modo da centrare la camera
	return Utility_GLM_MatrixFromVectors(CameraPos, scale, glm::vec3(0));
}


/*
Skybox::Skybox(const Model * Model)
{
	model = Model;
	scale = glm::vec3(1);
}

Skybox::~Skybox()
{
}

void Skybox::setScale(const glm::vec3 & S)
{
	scale = S;
}

const glm::vec3 & Skybox::getScale() const
{
	return scale;
}

const Model* Skybox::getModel() const
{
	return model;
}

const glm::mat4 Skybox::getMatrix(const glm::vec3& CameraPos) const
{
	//Calcolo la matrice dello skybox in modo da centrare la camera
	return Utility_GLM_MatrixFromVectors(CameraPos, scale, glm::vec3(0));
}
*/