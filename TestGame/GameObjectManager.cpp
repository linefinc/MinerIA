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

//void GameObjectManager::AddGameObject(shared_ptr<GameObject> object)
//{
//	listGameObjects->push_back(object);
//}

//shared_ptr<GameObject> GameObjectManager::findGameObjectByName(const string& Name)
//{
//	for(unsigned int index = 0; index < listGameObjects->size(); index++)
//	{
//		if(listGameObjects->at(index) == NULL)
//		{
//			if(listGameObjects->at(index)->GetName() == Name)
//			{
//				return listGameObjects->at(index);
//			}
//		}
//	}
//
//}