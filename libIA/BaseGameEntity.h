#pragma once

class BaseGameEntity
{
private:
	// Base Game Endity ID
	int ID;

public:
	BaseGameEntity(int ID)
	{
		this->ID = ID;// todo: singleton for single progressive ID
	}

	// 
	virtual void Update(void) = 0;

	int GetID()
	{
		return this->ID;
	}

};