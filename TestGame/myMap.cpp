#include "myMap.h"
#include "VectorUtils.h"

myMap::myMap(int width, int height,unsigned int ScreenWidth,unsigned int boxSide)// todo: cange coordiante sistem to fit with game coordinte
	:width(width),height(height),boxSide(boxSide),ScreenWidth(ScreenWidth),scale(1),minX(0),minY(0),maxX(0),maxY(0)
{
	map = new std::vector<MapItem> ();

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

unsigned char myMap::GetValue(int x, int y)
{
	return map->at(width*y+x).value;
}

void myMap::SetValue(int x, int y, unsigned char val)
{
	int index = width*y+x;
	map->at(index).value = val;

	if (val > 0)
	{
		map->at(index).sprite->setTexture(*TextureList->at(1),true);
	}
	else
	{
		map->at(index).sprite->setTexture(*TextureList->at(0),true);
	}

}


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

	if( map->at(width *y +x).value == 0)
	{
		return true;
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
