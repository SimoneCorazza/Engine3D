#include "Actor.hpp"

#include "Mesh.hpp"

#include "Utility_GLM.hpp"

/*
Actor::Actor(unsigned int ID, Scene* Scene) 
	: ItemScene(ID, Scene)
{


	model = nullptr;
	location = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	rotation = glm::vec3(0, 0, 0);
	param = nullptr;

	modelMatrix = glm::mat4(1);
}
*/
Actor::Actor()
{
	model = nullptr;
	location = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	rotation = glm::vec3(0, 0, 0);
	param = nullptr;

	modelMatrix = glm::mat4(1);
}

Actor::~Actor()
{
	delete param;
}



const glm::vec3 & Actor::getLocation() const
{
	return location;
}

const glm::vec3 & Actor::getScale() const
{
	return scale;
}

const glm::vec3 & Actor::getRotation() const
{
	return rotation;
}

const Model* Actor::getModel() const
{
	return model;
}

const glm::mat4 Actor::getModelMatrix() const
{
	return modelMatrix;
}

Box* Actor::getBox() const
{
	Box* b = model->getMesh()->getFrustumBox() * modelMatrix;
	return b;
}



void Actor::setLocation(const glm::vec3 & V)
{
	location = V;
	CalculateMatrix();
}

void Actor::setScale(const glm::vec3 & V)
{
	scale = V;
	CalculateMatrix();
}

void Actor::setRotation(const glm::vec3 & V)
{
	rotation = V;
	CalculateMatrix();
}

void Actor::setLocation(const float & X, const float & Y, const float & Z)
{
	location.x = X;
	location.y = Y;
	location.z = Z;
	CalculateMatrix();
}

void Actor::setScale(const float & X, const float & Y, const float & Z)
{
	scale.x = X;
	scale.y = Y;
	scale.z = Z;
	CalculateMatrix();
}

void Actor::setRotation(const float & X, const float & Y, const float & Z)
{
	rotation.x = X;
	rotation.y = Y;
	rotation.z = Z;
	CalculateMatrix();
}

void Actor::setModel(const Model* M)
{
	model = M;
	CalculateMatrix();
}

void Actor::Update(const UpdateParameters& P)
{

}

/*
void Actor::setActorParameters(ActorParameters * P)
{
	param = P;
}
*/

const ActorParameters * Actor::getActorParameters() const
{
	return param;
}

void Actor::CalculateMatrix()
{
	modelMatrix = Utility_GLM_MatrixFromVectors(location, scale, rotation);
}
