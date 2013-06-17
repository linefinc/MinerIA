#include "myMap.h"
#include "VectorUtils.h"
#include <limits>
#include <cmath>

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
	// base RedTexture
	
	RedTexture  = new sf::Texture();
	RedTexture->loadFromFile("../data/base/base_0010.png");
	TextureList->push_back(RedTexture);
	// base 003
	GreenTexture0  = new sf::Texture();
	GreenTexture0->loadFromFile("../data/base/base_0020.png");
	TextureList->push_back(GreenTexture0);
	// 
	GreenTexture1  = new sf::Texture();
	GreenTexture1->loadFromFile("../data/base/base_0021.png");
	TextureList->push_back(GreenTexture1);
	// base 008
	GreenTexture2  = new sf::Texture();
	GreenTexture2->loadFromFile("../data/base/base_0022.png");
	TextureList->push_back(GreenTexture2);
	// todo: fix
	// base 008 
	GreenTexture3  = new sf::Texture();
	GreenTexture3->loadFromFile("../data/base/base_0022.png");
	TextureList->push_back(GreenTexture3);

	for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++)
		{
			AddCell(x,y,cellType::walkable);
		}


	clock.restart();
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
		item.sprite->setTexture(*GreenTexture0,true);
		item.wheatLevel = 1;
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



void myMap::SetValue(int x, int y, unsigned char val,unsigned char wheatLevel )
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
			pItem->sprite->setTexture(*GreenTexture0,true);
			pItem->wheatLevel = wheatLevel;
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

void myMap::Update(void)
{
	if( clock.getElapsedTime().asSeconds() < 1)
	{
		return;
	}
	clock.restart();

	for (unsigned int index = 0; index < map->size(); index++)
	{
		unsigned int wheatLevel = map->at(index).wheatLevel;
		if( map->at(index).value == cellType::wheat)
		{
			myMap::MapItem* pItem = &map->at(index);
		
			// the same of max(15 , wheatLevel+1)
			pItem->wheatLevel++;	
			
			if( pItem->wheatLevel > 15)
			{
				pItem->wheatLevel = 15;
			}

			// 
			int myrand = rand() % 100;
			if( myrand < 50 )	// 5 % of probability
			{
				int x = pItem->x;
				int y = pItem->y;
				myrand = (rand() % 3) -1;	// rand from -1 to 1
				x += myrand;

				myrand = (rand() % 3) -1;	// rand from -1 to 1
				y += myrand;
				

				if(CellIsEmpty(x,y) == true) 
				{
					int w = GetCell(x,y)->wheatLevel;
					SetValue(x,y, cellType::wheat, w);
				}
				
			}

			//
			//	Update render
			//
			if(pItem->wheatLevel < 2)	// 0001b	0 - 1  
			{
				pItem->sprite->setTexture(*GreenTexture0,true);
				break;
			}
			if((pItem->wheatLevel > 1) && (pItem->wheatLevel < 4))	// 001xb	2 - 3
			{
				pItem->sprite->setTexture(*GreenTexture1,true);
				break;
			}
			if((pItem->wheatLevel > 3) && (pItem->wheatLevel < 8))	// 01xxb	4 - 7
			{
				pItem->sprite->setTexture(*GreenTexture2,true);
				break;
			}
			if(pItem->wheatLevel > 7) 	// 1xxxb	8 - 15
			{
				pItem->sprite->setTexture(*GreenTexture3,true);
				break;
			}
		}
	}
}