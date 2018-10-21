#include "Skybox.hpp"

#include "Mesh.hpp"
#include "Utility_GLM.hpp"

#include "DEBUG.hpp"

Skybox::Skybox(const Mesh* Mesh, const TextureCube* TextureCube)
{
	ASSERT(Mesh != nullptr && TextureCube != nullptr, "Skybox::Skybox(): params can not be null");

	mesh = Mesh;
	scale = glm::vec3(1); // Default scale: the same as the mesh
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
	// Calculate the skybox array in order to center the camera
	return Utility_GLM_MatrixFromVectors(CameraPos, scale, glm::vec3(0));
}