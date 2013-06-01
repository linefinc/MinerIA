#include "Miner.h"
#include <cstdio>
#include <cassert>
#include "VisitBankAndDepositGold.h"

Miner::Miner(int ID)
:BaseGameEntity(ID)
{
	this->MaxGoldCarried = 10;
	this->CC = 0;
	this->Fatigue = 0;
	this->Thist = 0;
	this->GoldCarried = 0;
	this->SetLocation(eLocations::Home);
	this->pCurrentState = &VisitBankAndDepositGoldIstance;
}


Miner::~Miner(void)
{
}

void Miner::Update(void)
{
	Thist++;
	if(pCurrentState != NULL)
	{
		pGlobalState->Execute(this);
	}

	if(pCurrentState != NULL)
	{
		pCurrentState->Execute(this);
	}
}

void Miner::ChangeState(State<Miner>* pNewState)
{
	assert(pCurrentState);
	assert(pNewState);

	pCurrentState->Exit(this);
	pCurrentState = pNewState;
	pNewState->Enter(this);
}

void Miner::RevertPreviusSatate(void)
{
	ChangeState(this->pPreviousState);
}