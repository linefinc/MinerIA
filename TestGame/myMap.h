#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "FindableMap.h"


class myMap: public FindableMap, public sf::Drawable
{
private:
	int width; 
	int height;
	unsigned int ScreenWidth;
	// draw implementation used form sfml
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	myMap(int width, int height,unsigned int ScreenWidth,unsigned int boxSide);
	~myMap(void);

	std::vector<sf::Sprite*> listSprite;
	std::vector<sf::Texture*>* TextureList;

	sf::Texture* GreenTexture;
	sf::Texture* GreyTexture;
	sf::Texture* RedTexture;

	unsigned int boxSide;

	


	unsigned char* map;

	unsigned char GetValue(int x, int y);

	void SetValue(int x, int y, unsigned char val);

	bool CellIsEmpty(int x,int y) const;

};

