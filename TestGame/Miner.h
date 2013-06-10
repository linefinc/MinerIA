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


class Miner: public BaseGameEntity, public GameObject , public sf::Drawable
{
private:
	State<Miner>* pGlobalState;
	State<Miner>* pCurrentState;
	State<Miner>* pPreviousState;

	
	
	void AddTexture(const char* filename);

	vector<sf::Texture*> textureList;


	sf::Vector2f GamePosition;
	sf::Sprite sprite;
	// draw implementation used form sfml
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
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

	int GetID(void) const {return ID;} ;

	string GetName() const { return string("Miner");} ;

	void setTexturebyID(unsigned int ID);

	sf::Vector2f GetGamePosition(void) const
	{
		return GamePosition;
	}


	void SetGamePosition(sf::Vector2f Position);

	const StaticGameObject* sgoHome;
	const StaticGameObject* sgoBank;
	const StaticGameObject* sgoMine;
	const myMap* map;

};


