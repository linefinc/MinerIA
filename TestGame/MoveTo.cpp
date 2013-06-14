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
	for(int index = 0 ; index < pf.Path.size() ; index++)
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
			
			// calc new angle
			sf::Vector2f newDirection = VectorUtils::Normalize(nextDestination - pEntity->GetGamePosition());
			float angle = atan2(newDirection.y,newDirection.x);
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