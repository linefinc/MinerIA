#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"

using namespace std;

class GameObjectManager
{
private:
	vector<shared_ptr<GameObject>>* listGameObjects;
public:
	GameObjectManager();
	~GameObjectManager(void);
};


