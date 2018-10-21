#pragma once

#include "Model.hpp"
#include "Box.hpp"

#include <glm\glm.hpp>

#include "ItemScene.hpp"

class ActorParameters;
class UpdateParameters;

// Class that represents an object that can be positioned in the scene
class Actor : public ItemScene
{
	// Model of the actor
	const Model* model;

	// Model matrix
	glm::mat4 modelMatrix;

	// Information encoded in the array:

	// Position occupied by the actor
	glm::vec3 location;

	// Stretch made to the model (default (1, 1, 1))
	glm::vec3 scale;

	// Rotation of the model on the respective axes
	glm::vec3 rotation;


	protected:
		// Actor parameters for the shader; null if there is no parameter
		// Memory deallocation performed by the Actor base class
		ActorParameters* param;


	public:
		Actor();
		~Actor();


	public:

		// Gets the location of the array
		const glm::vec3& getLocation() const;

		// Get the actor's scale vector
		const glm::vec3& getScale() const;

		// Get the actor's rotation
		const glm::vec3& getRotation() const;

		// Gets the actor's 3D model
		const Model* getModel() const;

		// Gets the model matrix
		const glm::mat4 getModelMatrix() const;

		// Gets the Box containing the actor's 3D model
		Box* getBox() const;


		void setLocation(const glm::vec3& V);
		void setScale(const glm::vec3& V);
		void setRotation(const glm::vec3& V);
		void setLocation(const float& X, const float& Y, const float& Z);
		void setScale(const float& X, const float& Y, const float& Z);
		void setRotation(const float& X, const float& Y, const float& Z);

		void setModel(const Model* M);

		// Update the actor
		// @param[in] P - Parameters for the actor
		virtual void Update(const UpdateParameters& P);

		// Gets the parameters of the actor (for rendering or other usage)
		// It can also return null
		const ActorParameters* getActorParameters() const;

	private:

		// Allows you to re-calculate the actor's matrix
		void CalculateMatrix();
};

