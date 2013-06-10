#pragma once
#include <string>
#include <SFML\Graphics.hpp>

using namespace std;

// generic object
class GameObject
{	
public:
	virtual int GetID() const= 0 ;

	virtual string GetName() const = 0 ; 

	virtual sf::Vector2f GetGamePosition(void) const = 0;

	virtual void SetGamePosition(sf::Vector2f Position) = 0;
};
