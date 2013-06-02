#include "Miner.h"
#include <cstdio>
#include <cassert>
#include "GoHomeAndSleep.h"

Miner::Miner(int ID)
:BaseGameEntity()
{
	this->ID = ID;

	// Behavior part
	this->MaxGoldCarried = 10;
	this->CC = 0;
	this->Fatigue = 0;
	this->Thist = 0;
	this->GoldCarried = 0;
	this->sgoBanck = NULL;
	this->sgoHome = NULL;
	this->sgoMine = NULL;
	this->velocity= 40.0f;

	//this->SetLocation(eLocations::Home); //todo: fix here
	this->pCurrentState = &GoHomeAndSleepIstance;
	this->pGlobalState = NULL;
	
	// render part
	this->setSize(sf::Vector2f(30.0f,30.0f));
	this->setFillColor(sf::Color::Blue);

	// starts the clock
	clock.restart();
}


Miner::~Miner(void)
{

}

void Miner::Update(void)
{
	Thist++;
	//if(pCurrentState != NULL)
	//{
	//	pGlobalState->Execute(this);
	//}

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
	// store Current state in Previous State
	pPreviousState = pCurrentState;
	// change state
	pCurrentState = pNewState;
	pNewState->Enter(this);
}

void Miner::RevertPreviusSatate(void)
{
	ChangeState(this->pPreviousState);
}