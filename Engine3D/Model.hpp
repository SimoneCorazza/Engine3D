#pragma once

class Mesh;
class Material;

// CLass of a model: a mesh with a binded material
class Model
{
	// Pointer to the model mesh
	const Mesh* mesh;

	// Pointer to the material that makes up the model
	const Material* material;


	public:
		Model(const Mesh* Mesh, const Material* Material);

		~Model();


	public:

		// Gets the model mesh
		const Mesh* getMesh() const;

		// Gets the texture of the model
		const Material* getMaterial() const;
};

