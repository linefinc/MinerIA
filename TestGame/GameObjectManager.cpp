#include "GameObjectManager.h"


GameObjectManager::GameObjectManager(void)
{
	listGameObjects = new vector<shared_ptr<GameObject>>();
}


GameObjectManager::~GameObjectManager(void)
{
	delete listGameObjects;
}
