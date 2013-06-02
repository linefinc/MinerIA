#pragma once
#include "Miner.h"
#include "State.h"
#include "Singleton.h"



class VisitBankAndDepositGold: public State<Miner>
{
public:

	void Enter(Miner* pEntity);

	void Execute(Miner* pEntity);

	void Exit(Miner* pEntity);
};

static VisitBankAndDepositGold VisitBankAndDepositGoldIstance;