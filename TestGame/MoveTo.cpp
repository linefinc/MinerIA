#include "MoveTo.h"
#include "VectorUtils.h"

void MoveTo::Enter(Miner* pEntity)
{
	pEntity->clock.restart();
	printf("%d:Enter in Move to state\n",pEntity->GetID());
	/*printf("%d:\tLocal Position(%f,%f)\n",pEntity->GetID(),pEntity->GetLocation().x,pEntity->GetLocation().y);
	printf("%d:\tDestiantion(%f,%f)\n",pEntity->GetID(),pEntity->Destiantion.x,pEntity->Destiantion.y);*/
}

void MoveTo::Execute(Miner* pEntity)
{
	
	
	sf::Time esliped = pEntity->clock.getElapsedTime();
	
	if(esliped.asMilliseconds() > 100)
	{
		pEntity->clock.restart();
		printf(".");
		float distance2 = VectorUtils::Distance2(pEntity->GetLocation(),pEntity->Destiantion);
		if( distance2 < 10.0f)	// todo: remove magic number
		{
			printf("\n");
			pEntity->RevertPreviusSatate();
		}
		else
		{
			sf::Vector2f dir = pEntity->Destiantion - pEntity->getPosition();
			dir = VectorUtils::Normalize(dir);

			float distaneTravaled = esliped.asMilliseconds()* pEntity->velocity/100;


			dir.x *= distaneTravaled;// todo: user lerp
			dir.y *= distaneTravaled;

			if(distance2 > VectorUtils::Length2(dir))
			{
				dir = pEntity->getPosition() + dir;
				pEntity->setPosition( dir);
			}
			else
			{
					pEntity->setPosition( pEntity->Destiantion);
			}
		}
		


	}
}

void MoveTo::Exit(Miner* pEntity)
{
	printf("%d:Exit Mote to state\n",pEntity->GetID());
}