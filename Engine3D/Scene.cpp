#include "Scene.hpp"

#include <algorithm> // For std::sort

#include "Engine.hpp"
#include "DEBUG.hpp"

#include "InputEngine.hpp"
#include "Point2.hpp"
#include "Material.hpp"

Scene::Scene()
{
	addedActors = 0;
	engine = nullptr;
	skybox = nullptr;
}


Scene::~Scene()
{
}

void Scene::Inizialize(Engine* E)
{
	engine = E;
	ambientLight = glm::vec3(0.5f, 0.5f, 0.5f); // Default setting of ambient light
	InizializeScene(); // Initialize the derived scene
}

void Scene::Update(const UpdateParameters& SceneUpdateParameters)
{
	const std::vector<Actor*>* a = getActors();
	// I update the actors
	for (int i = 0; i < a->size(); i++)
		(*a)[i]->Update(SceneUpdateParameters);

	// Update cameras:
	MapIterator<unsigned int, Camera*> c = getCameras();
	while (c.hasNext())
		c.next()->Update(SceneUpdateParameters.getElapsedTime());

	UpdateScene(SceneUpdateParameters); // Update the derived scene
}

void Scene::OnScreenResize(size_t NewWidth, size_t NewHeight)
{
	MapIterator<unsigned int, Camera*> c = getCameras();
	while (c.hasNext())
		c.next()->OnScreenReSize(NewWidth, NewHeight);
}

const std::vector<Actor*>* Scene::getActors()
{
	return &actors;
}

MapIterator<unsigned int, Camera*> Scene::getCameras()
{
	return MapIterator<unsigned int, Camera*>(cameras);
}

MapIterator<unsigned int, Light*> Scene::getLigths()
{
	return MapIterator<unsigned int, Light*>(lights);
}

const Skybox * Scene::getSkyBox()
{
	return skybox;
}

void Scene::RemoveItem(unsigned int ID)
{
	items.Remove(ID); // I remove the item from the list of items
	int index_a = IndexOfActor(ID);
	std::map<unsigned int, Camera*>::iterator it_c = cameras.find(ID);

	if (index_a != -1) // In the case the element to be removed is an actor
	{
		delete actors[index_a]; // I remove the actor
		actors.erase(actors.begin() + index_a); // I delete the actor from the actors
	}
	else if (it_c != cameras.end()) // In the case the element to be removed is a camera
	{
		delete it_c->second; // Disallocate the camera
		cameras.erase(it_c); // I remove the camera from the cameras list
	}
	else
		ASSERT(false, "Unkown case: id not present");
}

InputState * Scene::getLastInputState()
{
	return engine->getLastInputState();
}

Camera* Scene::InsertNewCamera(MeasureMode ModeOffset, float X, float Y, MeasureMode ModeSize, float Width, float Height)
{
	unsigned int id = items.getNextID(); // Since the ID is required for the camera, I "anticipate"
	Camera* c = new Camera(ModeOffset, X, Y, ModeSize, Width, Height);

	// Set the parameters of ItemScene
	c->id = id; // ID of the scene item
	c->scene = this; // Parent scene


	Point2 size = getLastInputState()->getWindowSize();
	c->OnScreenReSize(size.x, size.y);
	items.InsertNew(c); // I enter the camera (the id returned by this method must match the one contained in 'id')
	cameras.insert(std::pair<unsigned int, Camera*>(id, c)); // I also enter the camera in the list of cameras

	return c;
}

void Scene::InsertNewActor(Actor* A)
{
	if (A != nullptr) // Null not accepted
	{
		unsigned int id = items.getNextID(); // I have the anticipated ID of the actor

		// Set the parameters of ItemScene
		A->id = id; // ID of the scene item
		A->scene = this; // Imposed the mother scene

		items.InsertNew(A); // I insert the actor (the id returned by this method must match the one contained in 'id')
		actors.push_back(A); // I include the actor also in the list of actors
		addedActors++;
	}
}

Light* Scene::InsertNewLight()
{
	unsigned int id = items.getNextID();
	Light* l = new Light();

	// Set the parameters of ItemScene
	l->id = id; // ID of the scene item
	l->scene = this; // Imposed the mother scene

	items.InsertNew(l); // I insert the item (the id returned by this method must match the one contained in 'id')
	lights.insert(std::pair<unsigned int, Light*>(id, l)); // I enter the light also in the list of lights

	return l;
}

void Scene::InsertSkybox(const Skybox* Skybox)
{
	skybox = Skybox;
}

UI & Scene::getUI()
{
	return ui;
}

void Scene::Terminate()
{
	engine->EndGameLoop();
}

const RenderingEngineInfo & Scene::getRenderingEngineInfo()
{
	return engine->getRenderingEngineInfo();
}

// It allows to decree which actor between the two must be positioned first
// this in order to sort the array of actors for rendering
// The test orders the actors in the following way:
// 1) For shader
// 2) for textures (material properties)
// 3) for mesh
// NOTE: it does not matter that it is a precise order, the important thing is that all the actors with the same characteristics are grouped by weighting
// the factors mentioned above (for this a comparison is made between pointers)
bool ActorCompare(const Actor* a, const Actor* b)
{
	const Shader* a_shader = a->getModel()->getMaterial()->getShader();
	const Shader* b_shader = b->getModel()->getMaterial()->getShader();
	const Texture2D* a_texture = a->getModel()->getMaterial()->getTexture();
	const Texture2D* b_texture = b->getModel()->getMaterial()->getTexture();
	const Mesh* a_mesh = a->getModel()->getMesh();
	const Mesh* b_mesh = b->getModel()->getMesh();
	
	if (a_shader == b_shader)
	{
		if (a_texture == b_texture)
			return a_mesh < b_mesh;
		else
			return a_texture < b_texture;
	}
	else
		return a_shader < b_shader;
}

void InsertionSort(std::vector<Actor*>& actors, bool (*cmp)(const Actor* a, const Actor* b))
{
	for (int i = actors.size() - 1; i >= 0; i--)
	{
		int j = i - 1;
		while (j >= 0 && cmp(actors[j], actors[i]))
		{
			std::swap_ranges(actors.begin() + j, actors.begin() + j + 1, actors.begin() + i);
			j--;
		}
	}
}

void Scene::SortActors()
{
	if (addedActors > 0)
	{
		int n = actors.size() + addedActors;
		float complexIns = addedActors * n;
		float complexSor = (float)n * log2f(n);
		if (complexIns < complexSor)
			InsertionSort(actors, ActorCompare);
		else
			std::sort(actors.begin(), actors.end(), ActorCompare);
		addedActors = 0;
		addedActors = 0;
	}
}

glm::vec3 Scene::getAmbientLight() const
{
	return ambientLight;
}

int Scene::IndexOfActor(const Actor* A)
{
	if (A == nullptr)
		return -1;
	else
		return IndexOfActor(A->getID());
}

int Scene::IndexOfActor(unsigned int ID)
{
	int i = 0;
	while (i < actors.size() && actors[i]->getID() != ID)
		i++;

	return (i == actors.size()) ? -1 : i;
}


Actor * Scene::GetActor(unsigned int ID)
{
	int p = IndexOfActor(ID);
	if (p == -1)
		return nullptr;
	else
		return actors[p];
}