#pragma once
#include "Miner.h"
#include "State.h"
#include "Singleton.h"





class EnterMinAndDIigForNugget: public State<Miner>
{
public:
	void Enter(Miner* pEntity);

	void Execute(Miner* pEntity);

	void Exit(Miner* pEntity);
};

static EnterMinAndDIigForNugget EnterMinAndDIigForNuggetIstance;

