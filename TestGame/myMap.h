#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "FindableMap.h"


class myMap: public FindableMap
{
private:
	int width; 
	int height;

public:
	myMap(int width, int height, unsigned int boxSide);
	~myMap(void);

	std::vector<sf::Shape*> listShape;

	unsigned int boxSide;
public:
	


	unsigned char* map;

	unsigned char GetValue(int x, int y);

	void SetValue(int x, int y, unsigned char val);

	bool CellIsEmpty(int x,int y) const;

	void Render(sf::RenderWindow* window);
};

