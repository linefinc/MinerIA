#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "FindableMap.h"


class myMap: public FindableMap, public sf::Drawable
{
private:
	class MapItem
	{
	public:
		unsigned char value;
		sf::Sprite* sprite;
		int x;
		int y;
	public:
		// constructor
		MapItem()
		:value(0), sprite(NULL)
		{	}
		// constructor with value
		MapItem(unsigned char value)
		:value(value), sprite(NULL)
		{	}
		// constructor with value
	};

	int width; 
	int height;
	int scale;
	// ofset for negative value
	int minX;
	int minY;
	int maxX;
	int maxY;

	unsigned int ScreenWidth;
	// draw implementation used form sfml
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	MapItem* GetCell(int x, int y) const;
public:
	myMap(int width, int height,unsigned int ScreenWidth,unsigned int boxSide);
	~myMap(void);

	std::vector<sf::Texture*>* TextureList;

	sf::Texture* GreenTexture;
	sf::Texture* GreyTexture;
	sf::Texture* RedTexture;

	unsigned int boxSide;

	
	void Dump(const char* fileName) const;

	std::vector<MapItem>* map;

	void SetValue(int x, int y, unsigned char val);

	bool CellIsEmpty(int x,int y) const;
	
	void AddCell(int x, int y,unsigned char value);

	void setGridScale(int scale) 
	{
		this->scale = scale;
	}

	int getGridScale(void)
	{
		return scale;
	}
};

