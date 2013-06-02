#include "VisitBankAndDepositGold.h"
#include "EnterMinAndDIigForNugget.h"
#include "GoHomeAndSleep.h"
#include <cstdio>


void VisitBankAndDepositGold::Enter(Miner* pEntity)
{
	//todo: fix here
	//if(pEntity->GetLocation() != Miner::eLocations::Bank) 
	{
		//printf("%d:Enter to Bank\n",pEntity->GetID());
	//	pEntity->SetLocation(Miner::eLocations::Mine);
	}
}


void VisitBankAndDepositGold::Execute(Miner* pEntity)
{
	pEntity->CC += pEntity->GoldCarried;
	pEntity->GoldCarried = 0;
	printf("Total CC %d\n", pEntity->CC);
	if(pEntity->Fatigue > 30)
	{
		pEntity->ChangeState(&GoHomeAndSleepIstance);
	}
	else
	{
		pEntity->ChangeState(&EnterMinAndDIigForNuggetIstance);
	}
}


void VisitBankAndDepositGold::Exit(Miner* pEntity)
{
	printf("%d:Leave Bank\n",pEntity->GetID());
}
