// Standard library
#include <cstdio>
#include <memory>
#include <vector>
// SFML
#include <SFML/Graphics.hpp>
// my dev
#include "myMap.h"

using namespace std;


int main()
{
	
	// list of shared_ptr to handle sf::shape
	//vector<shared_ptr<sf::Shape>> ListShape();
	
	// setup video mode
	sf::RenderWindow window(sf::VideoMode(600, 600), "Miner works!");
    
	shared_ptr<sf::CircleShape> newCirle(new sf::CircleShape(10.0f));
	newCirle->setFillColor(sf::Color::Green);

	myMap* map = new myMap(window.getSize().x/ 30,window.getSize().y/ 30);

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

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
		map->Render(&window);
		window.draw(*newCirle);
        window.display();
    }

    return 0;
}