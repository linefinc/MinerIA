#include "GameObjectManager.h"

//
//GameObjectManager::GameObjectManager(void)
//{
//	listGameObjects = new vector<shared_ptr<GameObject>>();
//	NextID = 0;
//}
//
//
//GameObjectManager::~GameObjectManager(void)
//{
//	delete listGameObjects;
//}
//
int GameObjectManager::GetNextID(void)
{
	return NextID++;
}

void GameObjectManager::AddGameObject(shared_ptr<GameObject> object)
{
	listGameObjects->push_back(object);
}

shared_ptr<GameObject> GameObjectManager::findGameObjectByName(const string& Name)
{
	vector<shared_ptr<GameObject>>::iterator pos;

	for (pos = listGameObjects->begin(); pos != listGameObjects->end(); ++pos)
	{

		if (pos->get()->GetName() == Name)
		{
			return (shared_ptr<GameObject>)pos->get();
		}
	}

}