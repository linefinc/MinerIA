#include "MoveTo.h"
#include "VectorUtils.h"
#include "PathFinding.h"
#include <cmath>

#define PI 3.14159265359


void MoveTo::Enter(Miner* pEntity)
{
	pEntity->clock.restart();

	pEntity->listDestiantion.clear();

	Point2d start(pEntity->GetGamePosition().x,pEntity->GetGamePosition().y);// todo: cange coordiante sistem to fit with game coordinte
	Point2d end(pEntity->FinalDestiantion.x ,pEntity->FinalDestiantion.y);
	PathFinder pf(pEntity->map,start,end);
	bool rc = pf.calc();
	if( rc == false)
	{
		printf("error");
	}

	
	pf.Reverse();
	vector<Point2d> temp (pf.Path);
	pf.Optimize();

	// reverse order
	for(unsigned int index = 0 ; index < pf.Path.size() ; index++)
	{
		float x = pf.Path[index ].x;
		float y = pf.Path[index ].y;

		pEntity->listDestiantion.push_back(sf::Vector2f(x,y));
	}

}

void MoveTo::Execute(Miner* pEntity) // todo: review all function. Spaghetti flow code
{
	sf::Time esliped = pEntity->clock.getElapsedTime();
	

	if(esliped.asMilliseconds() > 100)	// check to avoid too small moviment
	{
		
		pEntity->clock.restart();		// reset counter
		//
		//	calc distance from destination and local position
		//
		sf::Vector2f nextDestination = pEntity->listDestiantion[0];
		// 
		//	calc distance travaled from the next render
		//	Note: 1e-3f = 1/1000
		//	
		float distaneTravaled = esliped.asMilliseconds()* pEntity->velocity * 1e-3f;


		if((distaneTravaled*distaneTravaled)< VectorUtils::Distance2(nextDestination,pEntity->GetGamePosition()))
		{
			//
			// here normal move
			//
			sf::Vector2f newDirection = VectorUtils::Normalize(nextDestination - pEntity->GetGamePosition());
			newDirection *= distaneTravaled;
			newDirection += pEntity->GetGamePosition();
			pEntity->SetGamePosition(newDirection);
			
		}
		else
		{
			//
			// close move.
			//
			pEntity->SetGamePosition(nextDestination);
			pEntity->listDestiantion.erase(pEntity->listDestiantion.begin());	// remove first element
			
		}

		if( pEntity->listDestiantion.size() > 0)
		{
			sf::Vector2f nextDestination = pEntity->listDestiantion[0];
			// calc new angle
			sf::Vector2f newDirection = VectorUtils::Normalize(nextDestination - pEntity->GetGamePosition());
			float angle = atan2(newDirection.y,newDirection.x) / PI *180.0;
			// TODO:recalc sprite number 
			// here recalc sprite number 
			SwitchSprite(pEntity,angle);
		}

		if( pEntity->listDestiantion.size() == 0)
		{				
			pEntity->RevertPreviusSatate();
		}
		
		
	


	}
}

void MoveTo::Exit(Miner* pEntity)
{
	printf("%d:Exit Mote to state\n",pEntity->GetID());
}



//
//	SwithSprite with angle
//
void MoveTo::SwitchSprite(Miner* pEntity,float angle)
{

	int iAngle = angle/45;


	switch(iAngle)
	{
	// fixed
	case 4:
	case -4:	//	180°
		pEntity->setTexturebyID(24);
		return;
	case -3:	//	135°
		pEntity->setTexturebyID(20);
		return;
	case -2:	//	90°
		pEntity->setTexturebyID(16);
		return;
	case -1:	//	45°
		pEntity->setTexturebyID(12);
		return;
	case 0:		//	0°
		pEntity->setTexturebyID(8);
		return;
	case 1:		//	45°
		pEntity->setTexturebyID(4);
		return;
	case 2:		//	90°
		pEntity->setTexturebyID(0);
		return;
	case 3:		//	90°
		pEntity->setTexturebyID(28);
		return;
	default:
		pEntity->setTexturebyID(33);
		return;
	}

}