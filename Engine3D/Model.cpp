#include "Model.hpp"



Model::Model(const Mesh* Mesh, const Material* Material)
{
	mesh = Mesh;
	material = Material;
}


Model::~Model()
{
}

const Mesh * Model::getMesh() const
{
	return mesh;
}

const Material * Model::getMaterial() const
{
	return material;
}
