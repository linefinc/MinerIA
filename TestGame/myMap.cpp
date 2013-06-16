#include "myMap.h"
#include "VectorUtils.h"
#include <limits>

myMap::myMap(int width, int height,unsigned int ScreenWidth,unsigned int boxSide)// todo: cange coordiante sistem to fit with game coordinte
	:boxSide(boxSide),ScreenWidth(ScreenWidth),scale(1)
{
	map = new std::vector<MapItem> ();
	// reset limit
	minX = INT_MAX;
	minY = INT_MAX;
	maxX = INT_MIN;
	maxY = INT_MIN;
	// texure array
	TextureList = new std::vector<sf::Texture*>();
	
	
	// load texture from file
	GreyTexture  = new sf::Texture();
	GreyTexture->loadFromFile("../data/base/base_0001.png");
	TextureList->push_back(GreyTexture);
	// base 002
	GreenTexture  = new sf::Texture();
	GreenTexture->loadFromFile("../data/base/base_0002.png");
	TextureList->push_back(GreenTexture);
	// base 003
	RedTexture  = new sf::Texture();
	RedTexture->loadFromFile("../data/base/base_0003.png");
	TextureList->push_back(RedTexture);

	for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++)
		{
			AddCell(x,y,cellType::walkable);
		}
}


myMap::~myMap(void)
{
}

//
//	Add cell to Maps
// 
void myMap::AddCell(int x, int y,unsigned char value)
{
	if( GetCell(x,y) != NULL)
	{
		return;
	}

	MapItem item;
	item.x =x;
	item.y = y;
	item.value = value;
	item.sprite = new sf::Sprite();
	item.sprite->setPosition(VectorUtils::ConvertToScreenSpace(x,y,ScreenWidth));
	
	switch(value)
	{
	case cellType::unwalkable:
		item.sprite->setTexture(*RedTexture,true);
		break;
	case cellType::walkable:
		item.sprite->setTexture(*GreyTexture,true);
		break;
	case cellType::wheat:
		item.sprite->setTexture(*GreenTexture,true);
		break;
	}
	
	map->push_back(item);

	// update limit
	if(x < minX)	minX = x;
	if(x > maxX)	maxX = x;
	if(y < minY)	minY = y;
	if(y > maxY)	maxY = y;

}

myMap::MapItem* myMap::GetCell(int x, int y) const
{
	// todo: use more efficient way to scan array
	for(unsigned int index = 0; index < map->size(); index++)
	{
		if((map->at(index).x == x) && (map->at(index).y == y))
		{
			return &(map->at(index));
		}
	}

	return NULL;
}

void myMap::SetValue(int x, int y, unsigned char val)
{
	myMap::MapItem* pItem = GetCell(x,y);
	
	if(pItem != NULL)
	{
		pItem->value = val;
		switch(val)
		{
		case cellType::unwalkable:
			pItem->sprite->setTexture(*RedTexture,true);
			break;
		case cellType::walkable:
			pItem->sprite->setTexture(*GreyTexture,true);
			break;
		case cellType::wheat:
			pItem->sprite->setTexture(*GreenTexture,true);
			break;
		}
		
	}
}

// Cell Is Empty
// return true if the cell is wolkable
// return flase if the cell is not wolkable
bool myMap::CellIsEmpty(int x,int y) const
{
	if(( x < minX) || (y < minY))
	{
		return false;
	}

	if(( x > maxX) || (y > maxY))
	{
		return false;
	}

	myMap::MapItem* pItem = GetCell(x,y);
	
	if(pItem != NULL)
	{
		return pItem->value != cellType::unwalkable;
	}

	return false;
}

void myMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(unsigned int index=0; index < map->size(); index++)
	{
		if(map->at(index).sprite)
		{
			target.draw(*map->at(index).sprite, states);
		}
	}

}

void myMap::Dump(const char* fileName) const
{
	FILE* fp = fopen(fileName,"w");
	if( fp == NULL)
	{
		return;
	}
	for(int y = minY; y <= maxY ; y++)
	{
		for(int x = minX; x <= maxX ; x++)
		{
			myMap::MapItem* pItem = GetCell(x,y);
			if( pItem == NULL)
			{
				fprintf(fp,"X;");
			}
			else
			{
				fprintf(fp,"%d;",pItem->value);
			}
		}
		fprintf(fp,"\n");
	}

	fclose(fp);
}