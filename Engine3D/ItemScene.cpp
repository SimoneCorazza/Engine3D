#include "ItemScene.h"

#include "Scene.h"

#include "DEBUG.h"

ItemScene::ItemScene()
{
	id = 0;
	scene = nullptr;
}

/*
ItemScene::ItemScene(unsigned int ID, Scene* Scene)
{
	id = ID;
	scene = Scene;
}
*/

ItemScene::~ItemScene()
{
}

unsigned int ItemScene::getID() const
{
	return id;
}

const Scene * ItemScene::getScene()
{
	return scene;
}

void ItemScene::RemoveFromScene()
{
	if (scene == nullptr)
		ASSERT(false, "Impossibile eliminare Item: non è agganciato a nessuna scena");
	else
		scene->RemoveItem(id); //Rimuovo l'item dalla scena
}

InputState * ItemScene::getInputState()
{
	return scene->getLastInputState();
}
