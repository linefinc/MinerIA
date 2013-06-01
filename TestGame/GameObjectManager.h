#pragma once
#include <vector>
#include <memory>
#include <string>
#include "GameObject.h"

using namespace std;


class GameObjectManager
{
private:
	// singleton
	//static GameObjectManager* instancePtr;
	vector<shared_ptr<GameObject>>* listGameObjects;

	int NextID;

	// private costructr
	
	
public:
	//static GameObjectManager* GetIstance() 
	//{
	//	if (instancePtr == NULL) 
	//	{
	//		instancePtr = new GameObjectManager();
	//	}
	//	return instancePtr;
	//}
	GameObjectManager();

	~GameObjectManager(void);

	shared_ptr<GameObject> findGameObjectByName(const string& Name);

	void AddGameObject(shared_ptr<GameObject> object);

	int GetNextID();
};

// initialize pointer
//GameObjectManager* GameObjectManager::instancePtr = NULL;
static GameObjectManager GameObjectManagerIstance;