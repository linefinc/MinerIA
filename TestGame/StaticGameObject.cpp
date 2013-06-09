#include "StaticGameObject.h"


StaticGameObject::StaticGameObject(int ID, string Name)
{
	
	this->ID = ID;
	this->Name = Name;
	// render part
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