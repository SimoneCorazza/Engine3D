#pragma once

class Mesh;
class Material;

// Class that represents a model of a textured object
class Model
{
	const Mesh* mesh; // Pointer to the model mesh
	const Material* material; // Pointer to the material that makes up the model


	public:
		Model(const Mesh* Mesh, const Material* Material);

		~Model();


	public:

		// Gets the model mesh
		const Mesh* getMesh() const;

		// Gets the texture of the model
		const Material* getMaterial() const;
};

