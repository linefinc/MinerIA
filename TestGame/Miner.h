#pragma once
#include <SFML\Graphics.hpp>
#include "BaseGameEntity.h"
#include "State.h"
#include "GameObject.h"


class Miner: public BaseGameEntity, public sf::RectangleShape, public GameObject
{
private:
	State<Miner>* pGlobalState;
	State<Miner>* pCurrentState;
	State<Miner>* pPreviousState;
	
public:
	sf::Vector2f Destiantion;
	int Thist;
	int GoldCarried;
	int CC;
	int Fatigue;
	int MaxGoldCarried;
	int ID;


public:
	// constuctor
	Miner(int ID);
	~Miner(void);

	void Update(void);

	void ChangeState(State<Miner>* pNewState);

	void RevertPreviusSatate(void);

	sf::Vector2f GetLocation(void) { return this->getPosition();};

	void SetLocation(sf::Vector2f loc) { this->setPosition(loc); };
	

	int GetID(void) const {return ID;} ;

	string GetName() const { return string("Miner");} ;
};

