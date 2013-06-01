#pragma once
#include <vector>
#include <SFML\Graphics.hpp>



class myMap
{
private:
	int width; 
	int height;

public:
	myMap(int width, int height);
	~myMap(void);

	std::vector<sf::Shape*> listShape;

public:



	unsigned char* map;

	unsigned char GetValue(int x, int y);

	void SetValue(int x, int y, unsigned char val);

	bool CellIsEmpty(int x,int y) const;

	void Render(sf::RenderWindow* window);
};

