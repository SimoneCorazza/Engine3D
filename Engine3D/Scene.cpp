#include "Scene.h"

#include <algorithm> //Per std::sort

#include "Engine.h"
#include "DEBUG.h"

#include "InputEngine.h"
#include "Point2.h"
#include "Material.h"

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
	ambientLight = glm::vec3(0.5f, 0.5f, 0.5f); //Impostazione di default della luce d'ambiente
	InizializeScene(); //Inizializzo la scena derivata
}

void Scene::Update(const UpdateParameters& SceneUpdateParameters)
{
	const std::vector<Actor*>* a = getActors();
	//Aggiorno gli attori
	for (int i = 0; i < a->size(); i++)
		(*a)[i]->Update(SceneUpdateParameters);

	//Aggiorno le camere:
	MapIterator<unsigned int, Camera*> c = getCameras();
	while (c.hasNext())
		c.next()->Update(SceneUpdateParameters.getElapsedTime());

	UpdateScene(SceneUpdateParameters); //Aggiorno la scena derivata
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
	items.Remove(ID); //Rimuovo l'elemento lall'elenco degli items
	int index_a = IndexOfActor(ID);
	std::map<unsigned int, Camera*>::iterator it_c = cameras.find(ID);

	if (index_a != -1) //Nel caso l'elemento da rimuovere è un'attore
	{
		delete actors[index_a]; //Disalloco l'attore
		actors.erase(actors.begin() + index_a); //Elimino l'attore dagli attori
	}
	else if (it_c != cameras.end()) //Nel caso l'elemento da rimuovere è una camera
	{
		delete it_c->second; //Disalloco la camera
		cameras.erase(it_c); //Elimino la camera dalle camere
	}
	else
		ASSERT(false, "Caso non previso: ID sconoscuto");
}

InputState * Scene::getLastInputState()
{
	return engine->getLastInputState();
}

Camera* Scene::InsertNewCamera(MeasureMode ModeOffset, float X, float Y, MeasureMode ModeSize, float Width, float Height)
{
	unsigned int id = items.getNextID(); //Siccome per la camera è richiesto l'ID faccio "anticipare"
	Camera* c = new Camera(ModeOffset, X, Y, ModeSize, Width, Height); //Istanzio una camera

	//Setto i parametri di ItemScene
	c->id = id; //ID dell'item della scena
	c->scene = this; //Scena madre


	Point2 size = getLastInputState()->getWindowSize();
	c->OnScreenReSize(size.x, size.y);
	items.InsertNew(c); //Inserisco la camera (l'id restituito da questo metodo deve corrispondere con quello contenuto in 'id')
	cameras.insert(std::pair<unsigned int, Camera*>(id, c)); //Inserisco la camera anche nell'elenco delle camere

	return c;
}

void Scene::InsertNewActor(Actor* A)
{
	if (A != nullptr) //Null non accettato
	{
		unsigned int id = items.getNextID(); //Mi facio anticipare l'ID dell'attore

		//Setto i parametri di ItemScene
		A->id = id; //ID dell'item della scena
		A->scene = this; //Imposto la scena madre

		items.InsertNew(A); //Inserisco l'attore (l'id restituito da questo metodo deve corrispondere con quello contenuto in 'id')
		actors.push_back(A); //Inserisco l'attore anche nell'elenco degli attori
		addedActors++;
	}
}

Light* Scene::InsertNewLight()
{
	unsigned int id = items.getNextID();
	Light* l = new Light();

	//Setto i parametri di ItemScene
	l->id = id; //ID dell'item della scena
	l->scene = this; //Imposto la scena madre

	items.InsertNew(l); //Inserisco l'item (l'id restituito da questo metodo deve corrispondere con quello contenuto in 'id')
	lights.insert(std::pair<unsigned int, Light*>(id, l)); //Inserisco la luce anche nell'elenco delle luci

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

//Consente di decretare quale attore tra i due deve essere posizionato prima
//questo allo scopo di ordinare l'array degli attori per il rendering
//Il test ordina gli attori nel segiunete modo:
//1) Per shder
//2) per texture (proprietà del materiale)
//3) per mesh
//NOTA: non importa che sia un ordine preciso, l'importante è che tutti gli attori con le stesse caratteristiche siano raggruppati pesando
//	i fattori sopra citati (per questo viene effettuato un confronto tra puntatori)
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