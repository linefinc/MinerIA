#pragma once
#include "BaseGameEntity.h"
#include "State.h"


class Miner: public BaseGameEntity
{
private:
	State<Miner>* pGlobalState;
	State<Miner>* pCurrentState;
	State<Miner>* pPreviousState;
	int _ID;

public:
	enum eLocations
	{
		Mine,
		Home,
		Bank,
	};

public:
	int Location;
	int Thist;
	int GoldCarried;
	int CC;
	int Fatigue;
	int MaxGoldCarried;



public:
	// constuctor
	Miner(int ID);
	~Miner(void);

	int GetID(void)
	{
		return _ID;
	}

	void Update(void);

	void ChangeState(State<Miner>* pNewState);

	void RevertPreviusSatate(void);

	int GetLocation(void) { return this->Location;};

	void SetLocation(int newLocation) { this->Location = newLocation; };
	


};

