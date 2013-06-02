#pragma once
#include "Miner.h"
#include "State.h"
#include "Singleton.h"

class GoHomeAndSleep: public State<Miner>
{
public:
	void Enter(Miner* pEntity);

	void Execute(Miner* pEntity);

	void Exit(Miner* pEntity);
};

static GoHomeAndSleep GoHomeAndSleepIstance;