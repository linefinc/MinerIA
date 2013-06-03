#include "MoveTo.h"
#include "VectorUtils.h"
#include "PathFinding.h"

void MoveTo::Enter(Miner* pEntity)
{
	pEntity->clock.restart();
	printf("%d:Enter in Move to state\n",pEntity->GetID());
	/*
	printf("%d:\tLocal Position(%f,%f)\n",pEntity->GetID(),pEntity->GetLocation().x,pEntity->GetLocation().y);
	printf("%d:\tDestiantion(%f,%f)\n",pEntity->GetID(),pEntity->Destiantion.x,pEntity->Destiantion.y);
	*/

	pEntity->listDestiantion.clear();
	unsigned int boxSide = pEntity->map->boxSide;

	Point2d start(pEntity->getPosition().x/ boxSide,pEntity->getPosition().y / boxSide);// todo: cange coordiante sistem to fit with game coordinte
	Point2d end(pEntity->FinalDestiantion.x /boxSide,pEntity->FinalDestiantion.y / boxSide);
	PathFinder pf(pEntity->map,start,end);
	bool rc = pf.calc();
	if( rc == false)
	{
		printf("error");
	}

	// reverse order
	for(int index = pf.Path.size() -1 ; index > -1 ; index--)
	{
		float x = pf.Path[index ].x * boxSide;
		float y = pf.Path[index ].y * boxSide;

		pEntity->listDestiantion.push_back(sf::Vector2f(x,y));
	}

}

void MoveTo::Execute(Miner* pEntity) // todo: review all function. Spaghetti flow code
{
	
	
	sf::Time esliped = pEntity->clock.getElapsedTime();
	
	//if(esliped.asMilliseconds() > 20)
	{
		
		
		pEntity->clock.restart();
		printf(".");
		sf::Vector2f nextDestination = pEntity->listDestiantion[0];
		float distance2 = VectorUtils::Distance2(pEntity->GetLocation(),nextDestination);
		if( distance2 < 10.0f)	// todo: remove magic number
		{
			if( nextDestination == pEntity->FinalDestiantion)
			{
				printf("\n");
				pEntity->RevertPreviusSatate();
				return;
			}
			else
			{
				pEntity->listDestiantion.erase(pEntity->listDestiantion.begin());
				printf("#");
			}
		}
		else
		{
			

			sf::Vector2f dir = nextDestination - pEntity->getPosition();
			dir = VectorUtils::Normalize(dir);

			// the same of "float distaneTravaled = esliped.asMilliseconds()* pEntity->velocity /1000;"
			float distaneTravaled = esliped.asMilliseconds()* pEntity->velocity * 1e-3f;


			dir.x *= distaneTravaled;// todo: user lerp
			dir.y *= distaneTravaled;

			if(distance2 > VectorUtils::Length2(dir))
			{
				pEntity->setPosition( nextDestination + dir);
			}
			else
			{
				pEntity->setPosition( nextDestination);

			}
		}
		


	}
}

void MoveTo::Exit(Miner* pEntity)
{
	printf("%d:Exit Mote to state\n",pEntity->GetID());
}