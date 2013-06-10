#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include "BaseGameEntity.h"
#include "State.h"
#include "GameObject.h"
#include "VectorUtils.h"

using namespace std;

class StaticGameObject:  public GameObject,  public sf::Drawable
{
private:
	int ID;
	string Name;

	// draw implementation used form sfml
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public: 
	sf::Sprite sprite;

	StaticGameObject(int ID, string Name);
	~StaticGameObject(void);

	int GetID() const;

	sf::Vector2f GamePosition;

	sf::Vector2f GetGamePosition(void) const
	{
		return GamePosition;
	}


	void SetGamePosition(sf::Vector2f Position)
	{
		GamePosition = Position;
		sprite.setPosition(VectorUtils::ConvertToScreenSpace(Position.x,Position.y,800));
	}

	string GetName() const;
};

