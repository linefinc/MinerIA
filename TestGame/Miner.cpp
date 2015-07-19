#include "Miner.h"
#include <cstdio>
#include <cassert>
#include "GoHomeAndSleep.h"
#include "GameObjectManager.h"

Miner::Miner(int ID)
	:BaseGameEntity()
{
	this->ID = ID;

	// Behavior part
	this->MaxGoldCarried = 10;
	this->CC = 0;
	this->Fatigue = 0;
	this->Thist = 0;
	this->GoldCarried = 0;
	this->sgoBank = NULL;
	this->sgoHome = NULL;
	this->sgoMine = NULL;
	this->velocity = 1.0f;

	//this->SetLocation(eLocations::Home); //todo: fix here
	this->pCurrentState = &GoHomeAndSleepIstance;
	this->pGlobalState = NULL;

	// render part
	AddTexture("../data/mower/0000.png");
	AddTexture("../data/mower/0001.png");
	AddTexture("../data/mower/0002.png");
	AddTexture("../data/mower/0003.png");
	AddTexture("../data/mower/0004.png");
	AddTexture("../data/mower/0005.png");
	AddTexture("../data/mower/0006.png");
	AddTexture("../data/mower/0007.png");
	AddTexture("../data/mower/0008.png");
	AddTexture("../data/mower/0009.png");

	AddTexture("../data/mower/0010.png");
	AddTexture("../data/mower/0011.png");
	AddTexture("../data/mower/0012.png");
	AddTexture("../data/mower/0013.png");
	AddTexture("../data/mower/0014.png");
	AddTexture("../data/mower/0015.png");
	AddTexture("../data/mower/0016.png");
	AddTexture("../data/mower/0017.png");
	AddTexture("../data/mower/0018.png");
	AddTexture("../data/mower/0019.png");

	AddTexture("../data/mower/0020.png");
	AddTexture("../data/mower/0021.png");
	AddTexture("../data/mower/0022.png");
	AddTexture("../data/mower/0023.png");
	AddTexture("../data/mower/0024.png");
	AddTexture("../data/mower/0025.png");
	AddTexture("../data/mower/0026.png");
	AddTexture("../data/mower/0027.png");
	AddTexture("../data/mower/0028.png");
	AddTexture("../data/mower/0029.png");
	AddTexture("../data/mower/0030.png");

	AddTexture("../data/mower/0031.png");
	AddTexture("../data/mower/0032.png");


	shared_ptr<GameObject> p = GameObjectManager::getInstance().findGameObjectByName("Home");

	//
	// setup 
	//
	sprite.setTexture(*textureList[0]);
	sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

	// starts the clock
	clock.restart();
}


Miner::~Miner(void)
{

}

void Miner::Update(void)
{
	Thist++;
	if (pCurrentState != NULL)
	{
		pCurrentState->Execute(this);
	}
}

void Miner::ChangeState(State<Miner>* pNewState)
{
	assert(pCurrentState);
	assert(pNewState);

	pCurrentState->Exit(this);
	// store Current state in Previous State
	pPreviousState = pCurrentState;
	// change state
	pCurrentState = pNewState;
	pNewState->Enter(this);
}

void Miner::RevertPreviusSatate(void)
{
	ChangeState(this->pPreviousState);
}

void Miner::AddTexture(const char* filename)
{
	// 
	//	load image 
	//
	sf::Texture* texture = new sf::Texture();
	if (texture->loadFromFile(filename) == false)
	{
		return;
		// Error...
	}

	textureList.push_back(texture);

}

void Miner::setTexturebyID(unsigned int ID)
{

	sprite.setTexture(*textureList[ID]);

}

void Miner::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

void Miner::SetGamePosition(sf::Vector2f Position)
{
	GamePosition = Position;
	sf::Vector2f screenPos = VectorUtils::ConvertToScreenSpace(Position.x, Position.y, 800);
	screenPos.y -= 32;
	sprite.setPosition(screenPos);
}