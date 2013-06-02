#include "StaticGameObject.h"


StaticGameObject::StaticGameObject(int ID, string Name)
{
	
	this->ID = ID;
	this->Name = Name;
	// render part
	this->setSize(sf::Vector2f(30.0f,30.0f));
	this->setFillColor(sf::Color::Yellow);
}


StaticGameObject::~StaticGameObject(void)
{
}


int StaticGameObject::GetID() const
{
	return ID;
}

string StaticGameObject::GetName() const
{
	return Name;
}