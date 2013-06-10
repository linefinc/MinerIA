#include "MoveTo.h"
#include "VectorUtils.h"
#include "PathFinding.h"
#include <cmath>

#define PI 3.14159265359


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

	Point2d start(pEntity->GetGamePosition().x/ boxSide,pEntity->GetGamePosition().y / boxSide);// todo: cange coordiante sistem to fit with game coordinte
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
		sf::Vector2f nextDestination = pEntity->listDestiantion[0];
		float distance2 = VectorUtils::Distance2(pEntity->GetGamePosition(),nextDestination);
	
		sf::Vector2f dir = nextDestination - pEntity->GetGamePosition();
		dir = VectorUtils::Normalize(dir);

		// the same of "float distaneTravaled = esliped.asMilliseconds()* pEntity->velocity /1000;"
		float distaneTravaled = esliped.asMilliseconds()* pEntity->velocity * 1e-3f;


		dir.x *= distaneTravaled;
		dir.y *= distaneTravaled;

		if(distance2 > VectorUtils::Length2(dir))
		{
			pEntity->SetGamePosition( nextDestination + dir);
		}
		else
		{
			pEntity->SetGamePosition( nextDestination);
			if( nextDestination == pEntity->FinalDestiantion)
			{
				pEntity->RevertPreviusSatate();
				return;
			}
			else
			{
				// erase the top position from list destiantion
				pEntity->listDestiantion.erase(pEntity->listDestiantion.begin());
				
				// calc the new angle from local and next positions
			//	sf::Vector2f dir = pEntity->listDestiantion[0] - pEntity->getPosition();
				
				//float angle = atan2f(dir.y,dir.x) *180 /PI;
				//SwitchSprite(pEntity,angle);
				
	
			}
		}
		
	


	}
}

void MoveTo::Exit(Miner* pEntity)
{
	printf("%d:Exit Mote to state\n",pEntity->GetID());
}

void MoveTo::SwitchSprite(Miner* pEntity,float angle)
{
	// value +1 = 0000'0001		0x01
	// value +0 = 0000'0000		0x00
	// value -1 = 1111'1111		0xFF
	
	// dx -1:0:+1
	// dy -1:0:+1

//	char value1 = dx & 0x0F;
//	char value2 = dy & 0xF0;
//	value2 = value2 << 4;
//	value2 += value1;

	int iAngle = angle/90*2;


	switch(iAngle)
	{
	

	case -2:	// 90°
		pEntity->setTexturebyID(5); // 0006.png ->(5)
		return;
	
	//case -1:	// 45°
	//	pEntity->setTexturebyID(9);	// 0003
	//	return;
	case 0:	// 0°
		pEntity->setTexturebyID(3); // 0004.png -> (3)
		return;
	/*case 1:	
		pEntity->setTexturebyID(9);	
		return;*/
	case 2:		//90°
		pEntity->setTexturebyID(1);	// 0002.png -> (1)
		return;
	case 4:		//180°
		pEntity->setTexturebyID(7);	// 0008.png	-> (7)
		return;
	default:
		return;
	}

//	pEntity->setTexturebyID(dx);

}