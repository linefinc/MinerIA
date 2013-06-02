#include "VisitBankAndDepositGold.h"
#include "EnterMinAndDIigForNugget.h"
#include "GoHomeAndSleep.h"
#include <cstdio>
#include "VectorUtils.h"
#include "MoveTo.h"

void VisitBankAndDepositGold::Enter(Miner* pEntity)
{
	//todo: fix here
	float distance2 = VectorUtils::Distance2(pEntity->GetLocation(),pEntity->sgoBanck->getPosition());
	if( distance2 > 10.0f)	// todo: remove magic number
	{
		pEntity->Destiantion = pEntity->sgoBanck->getPosition();
		pEntity->ChangeState(&MoveToIstance);
		return;
	}
	printf("%d:Enter to Banck\n",pEntity->GetID());
	pEntity->clock.restart();
}


void VisitBankAndDepositGold::Execute(Miner* pEntity)
{
	sf::Time esliped = pEntity->clock.getElapsedTime();
	if(esliped.asMilliseconds() > 1000)
	{
		pEntity->clock.restart();
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
	
}


void VisitBankAndDepositGold::Exit(Miner* pEntity)
{
	printf("%d:Leave Bank\n",pEntity->GetID());
}
