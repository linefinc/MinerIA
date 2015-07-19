#include <cstdio>
#include <cmath>
#include "VisitBankAndDepositGold.h"
#include "EnterMinAndDIigForNugget.h"
#include "GoHomeAndSleep.h"
#include "VectorUtils.h"
#include "MoveTo.h"



void EnterMinAndDIigForNugget::Enter(Miner* pEntity)
{
	//todo: fix here
	sf::Vector2f destination;
	bool rc = pEntity->map->NearestWheat(pEntity->GetGamePosition(), &destination);
	if (rc == false)
	{
		destination = pEntity->sgoMine->GetGamePosition();
		printf(" NO nearest wheat node\n");
	}
	else
	{
		printf("nearest wheat node %f %f\n", destination.x, destination.y);
	}

	float distance2 = VectorUtils::Distance2(pEntity->GetGamePosition(), destination);
	if (distance2 > 0.9f)	// todo: remove magic number
	{
		pEntity->FinalDestiantion = destination;
		pEntity->ChangeState(&MoveToIstance);
		return;
	}
	printf("%d:Enter to Min\n", pEntity->GetID());
	pEntity->clock.restart();

}


void EnterMinAndDIigForNugget::Execute(Miner* pEntity)
{
	sf::Time esliped = pEntity->clock.getElapsedTime();

	if (esliped.asMilliseconds() > 100)
	{
		pEntity->clock.restart();
		pEntity->GoldCarried += 1;
		pEntity->Fatigue += 1;

		sf::Vector2f pos = pEntity->GetGamePosition();
		unsigned int wheatLevel = pEntity->map->getWheatLevel(pos.x, pos.y);

		if (wheatLevel > 0)
		{
			printf(".");
			pEntity->map->SetValue(pos.x, pos.y, true, wheatLevel - 1);
		}
		else
		{
			//
			// cell don't have more wheat
			//
			sf::Vector2f destination;
			bool rc = pEntity->map->NearestWheat(pEntity->GetGamePosition(), &destination);
			if (rc == false)
			{
				printf(" NO nearest wheat node\n");
				pEntity->ChangeState(&GoHomeAndSleepIstance);
				return;
			}
			else
			{
				pEntity->ChangeState(&VisitBankAndDepositGoldIstance);
				return;
			}
		}
	}

	if (pEntity->GoldCarried >= pEntity->MaxGoldCarried)
	{
		printf("\n");
		pEntity->ChangeState(&VisitBankAndDepositGoldIstance);
	}
}

void EnterMinAndDIigForNugget::Exit(Miner* pEntity)
{
	printf("%d:Leave Min\n", pEntity->GetID());
}

