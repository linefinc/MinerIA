#include "myMap.h"
#include "VectorUtils.h"
#include <limits>

myMap::myMap(int width, int height,unsigned int ScreenWidth,unsigned int boxSide)// todo: cange coordiante sistem to fit with game coordinte
	:width(width),height(height),boxSide(boxSide),ScreenWidth(ScreenWidth),scale(1)
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
	sf::Texture* pTexture  = new sf::Texture();
	pTexture->loadFromFile("../data/base/base_0001.png");
	TextureList->push_back(pTexture);
	// base 002
	pTexture  = new sf::Texture();
	pTexture->loadFromFile("../data/base/base_0003.png");
	TextureList->push_back(pTexture);
	// base 003
	pTexture  = new sf::Texture();
	pTexture->loadFromFile("../data/base/base_0002.png");
	TextureList->push_back(pTexture);

	for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++)
		{
			
			sf::Sprite* rs= new sf::Sprite();				
			rs->setTexture(*TextureList->at(0),true);
			rs->setPosition(VectorUtils::ConvertToScreenSpace(x,y,ScreenWidth));
			
			AddCell(x,y,0,rs);
		}


}


myMap::~myMap(void)
{
}

void myMap::AddCell(int x, int y,unsigned char value, sf::Sprite* sprite)
{
	
	MapItem item;
	item.x =x;
	item.y = y;
	item.value = value;
	item.sprite = sprite;
	map->push_back(item);

	// update limit
	if(x < minX)
		minX = x;
	if(x > maxX)
		maxX = x;
	if(y < minY)
		minY = y;
	if(y > maxY)
		maxY = y;
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
		if (val > 0)
		{
			pItem->sprite->setTexture(*TextureList->at(1),true);
		}
		else
		{
			pItem->sprite->setTexture(*TextureList->at(0),true);
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
		return pItem->value == 0;
	}

	return false;
}

void myMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	unsigned int totalcount = width * height;

	for(unsigned int i=0; i < totalcount; i++)
	{
		if(map->at(i).sprite)
		{
			target.draw(*map->at(i).sprite, states);
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