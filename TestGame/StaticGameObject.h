#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include "BaseGameEntity.h"
#include "State.h"
#include "GameObject.h"

using namespace std;

class StaticGameObject: public sf::Sprite, public GameObject
{
	int ID;
	string Name;
public:
	StaticGameObject(int ID, string Name);
	~StaticGameObject(void);

	int GetID() const;

	string GetName() const;
};

