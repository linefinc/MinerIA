#pragma once
// standard library
#include <vector>
// 
#include <SFML\Graphics.hpp>

#include "BaseGameEntity.h"
#include "State.h"
#include "GameObject.h"
#include "StaticGameObject.h"
#include "VectorUtils.h"
#include "myMap.h"


class Miner: public BaseGameEntity, public sf::Sprite, public GameObject
{
private:
	State<Miner>* pGlobalState;
	State<Miner>* pCurrentState;
	State<Miner>* pPreviousState;

	
	
	void AddTexture(const char* filename);

	vector<sf::Texture*> textureList;
public:
	

	int Thist;
	int GoldCarried;
	int CC;
	int Fatigue;
	int MaxGoldCarried;
	int ID;
	float velocity;
	sf::Clock clock; // timer

	sf::Vector2f FinalDestiantion;
	std::vector<sf::Vector2f> listDestiantion;
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

	void setTexturebyID(unsigned int ID);


	const StaticGameObject* sgoHome;
	const StaticGameObject* sgoBank;
	const StaticGameObject* sgoMine;
	const myMap* map;

};


