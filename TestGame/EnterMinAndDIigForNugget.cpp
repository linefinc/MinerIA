#include <cstdio>
#include "VisitBankAndDepositGold.h"
#include "EnterMinAndDIigForNugget.h"
#include "GoHomeAndSleep.h"
#include "VectorUtils.h"
#include "MoveTo.h"



void EnterMinAndDIigForNugget::Enter(Miner* pEntity)
{
	//todo: fix here
	float distance2 = VectorUtils::Distance2(pEntity->GetLocation(),pEntity->sgoMine->getPosition());
	if( distance2 > 10.0f)	// todo: remove magic number
	{
		pEntity->Destiantion = pEntity->sgoMine->getPosition();
		pEntity->ChangeState(&MoveToIstance);
		return;
	}
	printf("%d:Enter to Min\n",pEntity->GetID());
	pEntity->clock.restart();

}


void EnterMinAndDIigForNugget::Execute(Miner* pEntity)
{
	sf::Time esliped = pEntity->clock.getElapsedTime();

	if(esliped.asMilliseconds() > 100)
	{
		pEntity->clock.restart();
		pEntity->GoldCarried += 1;
		pEntity->Fatigue +=1;
		printf(".");
	}

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

