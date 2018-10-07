#pragma once

#include "InputState.hpp"
class Scene;

// Represents an element of a scene: Camera, Actor, ...
// which requires an identifier and an ID
class ItemScene
{
	friend Scene; // TO SET THE PARAMETERS: ID and scenes

	unsigned int id; // ID of the item; unique in the scene
	Scene* scene; // Scene containing the item

	public:
		ItemScene();
		~ItemScene();


	public:

		// Gets the ID of the item according to the scene
		unsigned int getID() const;

		// Gets the scene containing the item
		const Scene* getScene();

		// It allows you to remove this element from the scene
		// NOTE: the object will be destroyed (delete obj)
		void RemoveFromScene();

	protected:

		// Gets the last state of the input for the scene
		InputState* getInputState();
};

