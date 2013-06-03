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

using namespace std;


int main()
{
	//inizalizze gameObj
	

	GameObjectManager& gom = GameObjectManager::getInstance();

	// setup video mode
	sf::RenderWindow window(sf::VideoMode(600, 600), "Miner works!");
    
	shared_ptr<sf::CircleShape> newCirle(new sf::CircleShape(10.0f));
	newCirle->setFillColor(sf::Color::Green);

	myMap* map = new myMap(window.getSize().x/ 30,window.getSize().y/ 30, 30);
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
	sgoHome->setPosition(1.0f*30,5.0f*30);
	
	//
	//	Setup Mine
	//
	StaticGameObject* sgoMine = new StaticGameObject(gom.GetNextID(),"MINE");
	sgoMine->setPosition(8.0f*30,1.0f*30);
	sgoMine->setFillColor(sf::Color::Magenta);
	//
	//	Setup Banck
	//
	StaticGameObject* sgoBanck = new StaticGameObject(gom.GetNextID(),"BANCK");
	sgoBanck->setPosition(10.0f*30,10.0f*30);
	sgoBanck->setFillColor(sf::Color::Black);
	//
	//	Miner setup
	//
	shared_ptr<Miner> myMiner (new Miner(gom.GetNextID()));
	myMiner->setPosition(sgoHome->getPosition());	// setup miner at home
	myMiner->sgoBanck = sgoBanck;
	myMiner->sgoHome  = sgoHome;
	myMiner->sgoMine = sgoMine;
	myMiner->map = map;
	myMiner->velocity = 4e-2;
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
		myMiner->Update();

		// render
        window.clear();
		map->Render(&window);
		
		window.draw(*sgoBanck);
		window.draw(*sgoHome);
		window.draw(*sgoMine);
		window.draw(*myMiner);

        window.display();
    }

    return 0;
}