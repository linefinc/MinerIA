#include <cstdio>
#include "GameObjectManager.h"
#include "VisitBankAndDepositGold.h"
#include "EnterMinAndDIigForNugget.h"
#include "GoHomeAndSleep.h"
#include "StaticGameObject.h"


void GoHomeAndSleep::Enter(Miner* pEntity)
{
	//todo: fix here
	//StaticGameObject* sgo =(StaticGameObject*) GameObjectManager.getInstance().findGameObjectByName("HOME").get();


	
	if(pEntity->GetLocation() != sf::Vector2f(2.0f,4.0f))
	{
		printf("%d:Enter to Home\n",pEntity->GetID());
	}
	printf("%d:Sleep",pEntity->GetID());
	pEntity->clock.restart();
}


void GoHomeAndSleep::Execute(Miner* pEntity)
{
	sf::Time esliped = pEntity->clock.getElapsedTime();
	if(esliped.asMilliseconds() > 100)
	{
		pEntity->clock.restart();
		pEntity->Fatigue -= 3;
		printf(".");
	}
	
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
