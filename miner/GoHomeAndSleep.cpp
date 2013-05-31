#include "VisitBankAndDepositGold.h"
#include "EnterMinAndDIigForNugget.h"
#include "GoHomeAndSleep.h"
#include <cstdio>

void GoHomeAndSleep::Enter(Miner* pEntity)
{
	if(pEntity->GetLocation() != Miner::eLocations::Home)
	{
		printf("%d:Enter to Home\n",pEntity->GetID());
	}
	printf("%d:Sleep",pEntity->GetID());
}


void GoHomeAndSleep::Execute(Miner* pEntity)
{
	pEntity->Fatigue -= 3;
	printf(".");
	if(pEntity->Fatigue <=0)
	{
		printf("\n");
		pEntity->Fatigue = 0;
		pEntity->ChangeState(&EnterMinAndDIigForNuggetIstance);
	}
}

void GoHomeAndSleep::Exit(Miner* pEntity)
{
	printf("%d:Leave Home\n",pEntity->GetID());
}
