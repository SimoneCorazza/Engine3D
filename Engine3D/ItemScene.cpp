#include "ItemScene.hpp"

#include "Scene.hpp"

#include "DEBUG.hpp"

ItemScene::ItemScene()
{
	id = 0;
	scene = nullptr;
}

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
		ASSERT(false, "Cannot remove: this item is not bound to a scene");
	else
		scene->RemoveItem(id);
}

InputState * ItemScene::getInputState()
{
	return scene->getLastInputState();
}
