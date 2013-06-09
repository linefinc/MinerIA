#pragma once
#include "Miner.h"
#include "State.h"
#include "Singleton.h"


class MoveTo :public State<Miner>
{
public:
	void Enter(Miner* pEntity);

	void Execute(Miner* pEntity);

	void Exit(Miner* pEntity);

	void SwitchSprite(Miner* pEntity,float angle);
};

static MoveTo MoveToIstance;
