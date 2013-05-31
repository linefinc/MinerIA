#include "VisitBankAndDepositGold.h"
#include "EnterMinAndDIigForNugget.h"
#include "GoHomeAndSleep.h"
#include <cstdio>


void EnterMinAndDIigForNugget::Enter(Miner* pEntity)
{
	if(pEntity->GetLocation() != Miner::eLocations::Mine)
	{
		printf("%d:Enter to Min\n",pEntity->GetID());
		pEntity->SetLocation(Miner::eLocations::Mine);
	}
	printf("%d:Pick Up Gold ",pEntity->GetID());
}


void EnterMinAndDIigForNugget::Execute(Miner* pEntity)
{
	pEntity->GoldCarried += 1;
	pEntity->Fatigue +=1;
	printf(".");
	if(pEntity->GoldCarried >= pEntity->MaxGoldCarried)
	{
		printf("\n");
		pEntity->ChangeState(&VisitBankAndDepositGoldIstance);
	}
}

void EnterMinAndDIigForNugget::Exit(Miner* pEntity)
{
	printf("%d:Leave Min\n",pEntity->GetID());
}

