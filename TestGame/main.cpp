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

	for(int y = -20; y < 30 ; y++)
		for(int x = -20; x < 30; x++)
		{
			sf::Vector2f screenPos = VectorUtils::ConvertToScreenSpace(x,y,800);
			if((screenPos.x >-64) &&(screenPos.x < 800)&&
				(screenPos.y > -32)&&(screenPos.y < 600))
			map->AddCell(x,y,0);
		}
	
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
	
	
	map->SetValue(8,10,1);
	map->SetValue(9,10,1);
	map->SetValue(10,8,1);
	map->SetValue(10,9,1);
	map->SetValue(9,9,1);
	map->SetValue(9,8,1);
	map->SetValue(8,9,1);
	map->SetValue(8,8,1);


	//
	//	Setup Home
	//
	StaticGameObject* sgoHome = new StaticGameObject(gom.GetNextID(),"HOME");
	sgoHome->SetGamePosition(sf::Vector2f(1.0f,5.0f));

	sf::Texture* pTextureHome  = new sf::Texture();
	pTextureHome->loadFromFile("../data/base/base_0005.png");
	sgoHome->sprite.setTexture(*pTextureHome);

	//
	//	Setup Mine
	//
	StaticGameObject* sgoMine = new StaticGameObject(gom.GetNextID(),"MINE");
	sgoMine->SetGamePosition(sf::Vector2f(8.0f,1.0f));
	
	sf::Texture* pTextureMine  = new sf::Texture();
	pTextureMine->loadFromFile("../data/base/base_0006.png");
	sgoMine->sprite.setTexture(*pTextureMine);
	//
	//	Setup Bank
	//
	StaticGameObject* sgoBank = new StaticGameObject(gom.GetNextID(),"BANK");
	sgoBank->SetGamePosition(sf::Vector2f(10.0f,10.0f));

	sf::Texture* pTextureBank  = new sf::Texture();
	pTextureBank->loadFromFile("../data/base/base_0004.png");
	sgoBank->sprite.setTexture(*pTextureBank);

	//
	//	Setup RAFINERY
	//
	StaticGameObject* sgoRafinery = new StaticGameObject(gom.GetNextID(),"RAFINERY");
	

	sf::Texture* pTextureRafinery  = new sf::Texture();
	bool rc = pTextureRafinery->loadFromFile("../data/refinery/0001.png");
	if(rc == false)
	{
		printf("error\n");
	}
	sgoRafinery->sprite.setTexture(*pTextureRafinery);

	int dx = 1;
	int dy = pTextureRafinery->getSize().y / 32  - 1;

	sgoRafinery->SetGamePosition(sf::Vector2f(10.0f - dx - dy ,10.0f - dy +dx));
	
	//map->SetValue(8,10,1);
	//map->SetValue(9,10,1);
	//map->SetValue(10,8,1);
	//map->SetValue(10,9,1);
	//map->SetValue(9,9,1);
	//map->SetValue(9,8,1);
	//map->SetValue(8,9,1);
	//map->SetValue(8,8,1);


	//
	//	Miner setup
	//
	shared_ptr<Miner> myMiner (new Miner(gom.GetNextID()));
	
	myMiner->SetGamePosition(sgoHome->GetGamePosition());	// setup miner at home
	myMiner->sgoBank = sgoBank;
	myMiner->sgoHome  = sgoHome;
	myMiner->sgoMine = sgoMine;
	myMiner->map = map;
	myMiner->velocity = 4.0f;
	
	//
	//	text
	//
	sf::Font font;
	if (!font.loadFromFile("../data/sansation.ttf"))
	{
		// error...
	}

	sf::Text textFps;
	textFps.setFont(font);
	textFps.setCharacterSize(24);
	textFps.setColor(sf::Color::Red);
	textFps.setStyle(sf::Text::Bold);
	textFps.setString("fps");

	sf::Text textRenderTime (textFps);
	textRenderTime.setString("render time");
	textRenderTime.setPosition(0.0f,24.0f);
	//
	//	Main loop
	//

	sf::Clock clock;
	clock.restart();
	float lastTime = 0;

	unsigned int counter = 0;

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

		int renderTime = clock.getElapsedTime().asMilliseconds() ;
		if(renderTime >= 100)
		{
			

			char str [50];
			sprintf_s(str,sizeof(str),"Render Time %d ms",renderTime/counter);
			textRenderTime.setString(str);

			unsigned int fps = 1000* counter / renderTime ;
			sprintf_s(str,sizeof(str),"fps %d",fps);
			textFps.setString(str);


			clock.restart();
			counter = 0;
		}
		counter++;
		// update
		myMiner->Update();

		// render
        window.clear();
		window.draw(*map);
		
		window.draw(*sgoBank);
		window.draw(*sgoHome);
		window.draw(*sgoMine);
		window.draw(*sgoRafinery);
		window.draw(*myMiner);
		window.draw(textFps);
		window.draw(textRenderTime);
		
		window.display();
    }

    return 0;
}


