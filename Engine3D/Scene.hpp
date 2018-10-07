#pragma once

#include <vector>


#include "IDCollection.hpp"
#include "MapIterator.hpp"

#include "Actor.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Skybox.hpp"

#include "UI.hpp"

#include "ItemScene.hpp"

#include "UpdateParameters.hpp"
#include "RenderingEngineInfo.hpp"

class Engine;

// Class that represents a scene of the game
class Scene
{
	// Actors present within the scene
	// Vector sorted according to the order rendering order
	// Shader
	// Texture
	// Properties of the material
	// Mesh (Verteces buffers)
	std::vector<Actor*> actors;
	unsigned int addedActors; // Number of actors added since the last sorting operation
	std::map<unsigned int, Light*> lights; // Lights present in the scene
	std::map<unsigned int, Camera*> cameras; // Rooms used for rendering
	UI ui;


	IDCollection<ItemScene*> items; // Any Item contained in the scene: rooms, actors, lights, ...

	Engine* engine; // Engine belonging to the scene

	const Skybox* skybox; // Skybox of the scene

	protected:

		glm::vec3 ambientLight; // Ambient light of the scene, used in shaders that support lighting

	public:
		Scene();
		~Scene();

	public:

		// Initialize the scene
		void Inizialize(Engine* E);

		// Updates the scene
		// @param [in] SceneUpdateParameters - Parameters for the scene
		void Update(const UpdateParameters& SceneUpdateParameters);

		// Method to call when the game window is resized
		void OnScreenResize(size_t NewWidth, size_t NewHeight);

		// Gets the actors contained in the scene
		const std::vector<Actor*>* getActors();

		// Get the rooms
		MapIterator<unsigned int, Camera*> getCameras();

		// Gets the lights present in the scene
		MapIterator<unsigned int, Light*> getLigths();

		// Gets the skybox of the scna (if it is null is not present in the scene)
		const Skybox* getSkyBox();

		// Remove the item with the indicated ID
		// NOTE: method called automatically by ItemScene.RemoveFromScene ()
		void RemoveItem(unsigned int ID);

		// Gets the last state of the input occurred during the last update of the scene
		InputState* getLastInputState();

		// It allows you to sort the array of actors to optimize the rendering time
		void SortActors();

		// Gets the ambient light of the scene, used in shaders that support lighting
		glm::vec3 getAmbientLight() const;

		// Gets the UI of the scene
		UI& getUI();

	protected:


		// --- METHODS TO BE EREDITED

		// It allows you to initialize your scene
		virtual void InizializeScene() abstract;

		// Updates the scene
		virtual void UpdateScene(const UpdateParameters& SceneUpdateParameters) abstract;

		// --- METHODS USED FROM THE DERIVED SCENE

		// Gets a new Camera object for the scene
		// @param [in] ModeOffset - Desired measurement mode for camera offset
		// @param [in] X - Desired measurement mode for the camera size
		// @param [in] Y - Desired measurement mode for camera size
		// @param [in] ModeSize - Desired measurement mode for the camera size
		// @param [in] Width - Length of the camera relative to the window (using the mode indicated above)
		// @param [in] Height - camera height compared to the window (using the mode indicated above)
		// @return Camera created
		Camera* InsertNewCamera(MeasureMode ModeOffset, float X, float Y, MeasureMode ModeSize, float Width, float Height);

		// Inserts a new actor for the scene
		// @param [in] Actor to add; not null
		void InsertNewActor(Actor* A);

		// Inserts a new light for the scene
		// @return Light created
		Light* InsertNewLight();

		// Set / insert a new Skybox, it can be null
		void InsertSkybox(const Skybox* Skybox);

		// Allows to terminate the engine
		void Terminate();

		// @return Information on the work of the engine
		const RenderingEngineInfo& getRenderingEngineInfo();

	private:
		

		// Gets the position index in the actor's array
		// @param [in] A - Desired actor
		// @return index in "actors" if not found or the argument is null returns -1
		int IndexOfActor(const Actor* A);
		// Gets the position index in the actor's array
		// @param [in] ID - ID of the actor
		// @return index in "actors" if not found -1
		int IndexOfActor(unsigned int ID);

		// Gets the actor with the indicated id
		// @param [in] ID - ID of the desired actor
		// @return Actor desired or null if not present
		Actor* GetActor(unsigned int ID);

		
};