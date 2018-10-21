#pragma once

#include "InputState.hpp"
class Scene;

// Represents an element of a scene: Camera, Actor, ...
// which requires an identifier and an ID
class ItemScene
{
	friend Scene; // TO SET THE PARAMETERS: ID and scenes

	// ID of the item; unique in the scene
	unsigned int id;

	// Scene containing the item
	Scene* scene;

	public:
		ItemScene();
		~ItemScene();


	public:

		// Gets the ID of the item according to the scene
		unsigned int getID() const;

		// Gets the scene containing the item
		const Scene* getScene();

		// It allows you to remove this element from the scene
		// @NOTE: the memory deallocation will be handled internally
		void RemoveFromScene();

	protected:

		// Gets the last state of the input for the scene
		InputState* getInputState();
};

