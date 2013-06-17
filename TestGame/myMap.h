#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "FindableMap.h"

enum cellType
{
	unwalkable =1,
	walkable = 2,
	wheat = 4,
};


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
		unsigned char wheatLevel;
	public:
		// constructor
		MapItem()
		:value(0), sprite(NULL), wheatLevel(0)
		{	}
		// constructor with value
		MapItem(unsigned char value)
		{	
			MapItem();
			this->value = value;
		}
		// constructor with value
	};

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

	
	sf::Texture* GreyTexture;
	sf::Texture* RedTexture;
	sf::Texture* GreenTexture0;
	sf::Texture* GreenTexture1;
	sf::Texture* GreenTexture2;
	sf::Texture* GreenTexture3;
	unsigned int boxSide;

	
	void Dump(const char* fileName) const;

	std::vector<MapItem>* map;

	void SetValue(int x, int y, unsigned char val,unsigned char wheatLevel = 0);

	bool CellIsEmpty(int x,int y) const;
	
	void AddCell(int x, int y,unsigned char value);

	void Update(void);

	void setGridScale(int scale) 
	{
		this->scale = scale;
	}

	int getGridScale(void)
	{
		return scale;
	}

	sf::Clock clock; // timer
};

