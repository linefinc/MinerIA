// Standard library
#include <cstdio>
#include <memory>
#include <vector>
// SFML
#include <SFML/Graphics.hpp>
// my dev
#include "myMap.h"
#include "Miner.h"
#include "GameObjectManager.h"
#include "StaticGameObject.h"
#include "cResurceManager.h"

using namespace std;

int main()
{
	// nit resurce manager
	cResurceManager* ResurceManager = new cResurceManager();

	//inizalizze gameObj
	GameObjectManager& gom = GameObjectManager::getInstance();

	// setup video mode
	sf::RenderWindow window(sf::VideoMode(800, 600), "Miner works!");

	//myMap* map = new myMap(window.getSize().x/ 30,window.getSize().y/ 30, 30);
	myMap* map = new myMap(12,12,800,32);
	//
	// init maps
	//
	map->SetValue(1,7,1);
	map->SetValue(2,2,1);
	map->SetValue(2,3,1);
	map->SetValue(2,4,1);
	map->SetValue(2,5,1);
	map->SetValue(2,6,1);
	map->SetValue(2,7,1);
	map->SetValue(3,4,1);
	map->SetValue(4,4,1);
	map->SetValue(5,4,1);
	map->SetValue(6,4,1);
	map->SetValue(7,4,1);
	map->SetValue(7,5,1);
	map->SetValue(7,6,1);
	map->SetValue(7,7,1);
	map->SetValue(7,8,1);
	map->SetValue(7,9,1);

	map->SetValue(5,0,1);
	map->SetValue(5,1,1);
	map->SetValue(5,2,1);
	
	//
	//	Setup Home
	//
	StaticGameObject* sgoHome = new StaticGameObject(gom.GetNextID(),"HOME");
	sgoHome->setPosition(VectorUtils::ConvertToScreenSpace(1,5,800));
	
	sf::Texture* pTextureHome  = new sf::Texture();
	pTextureHome->loadFromFile("../data/base/base_0004.png");
	sgoHome->setTexture(*pTextureHome);

	//
	//	Setup Mine
	//
	StaticGameObject* sgoMine = new StaticGameObject(gom.GetNextID(),"MINE");
	sgoMine->setPosition(VectorUtils::ConvertToScreenSpace(8,1,800));
	
	sf::Texture* pTextureMine  = new sf::Texture();
	pTextureMine->loadFromFile("../data/base/base_0006.png");
	sgoMine->setTexture(*pTextureMine);
	//
	//	Setup Bank
	//
	StaticGameObject* sgoBank = new StaticGameObject(gom.GetNextID(),"BANK");
	sgoBank->setPosition(VectorUtils::ConvertToScreenSpace(10,10,800));

	sf::Texture* pTextureBank  = new sf::Texture();
	pTextureBank->loadFromFile("../data/base/base_0004.png");
	sgoBank->setTexture(*pTextureBank);
	//
	//	Miner setup
	//
	shared_ptr<Miner> myMiner (new Miner(gom.GetNextID()));
	myMiner->setPosition(sgoHome->getPosition());	// setup miner at home
	myMiner->sgoBank = sgoBank;
	myMiner->sgoHome  = sgoHome;
	myMiner->sgoMine = sgoMine;
	myMiner->map = map;
	myMiner->velocity = 4e-2f;
	
	//
	//
	//

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
			{
                window.close();
			}
        }

		// update
		//myMiner->Update();

		// render
        window.clear();
		map->Render(&window);
		
		window.draw(*sgoBank);
		window.draw(*sgoHome);
		window.draw(*sgoMine);
		window.draw(*myMiner);
        window.display();
    }

    return 0;
}


