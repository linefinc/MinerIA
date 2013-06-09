#include "myMap.h"


myMap::myMap(int width, int height,unsigned int boxSide)// todo: cange coordiante sistem to fit with game coordinte
	:width(width),height(height),boxSide(boxSide)
{
	map = new unsigned char [width * height];
	memset(map, 0, width * height);


	// texure array
	TextureList = new std::vector<sf::Texture*>();
	
	
	// load texture from file
	sf::Texture* pTexture  = new sf::Texture();
	pTexture->loadFromFile("../data/base/base_0001.png");
	TextureList->push_back(pTexture);
	// base 002
	pTexture  = new sf::Texture();
	pTexture->loadFromFile("../data/base/base_0002.png");
	TextureList->push_back(pTexture);
	// base 003
	pTexture  = new sf::Texture();
	pTexture->loadFromFile("../data/base/base_0003.png");
	TextureList->push_back(pTexture);
	




	for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++)
		{
			unsigned int i = width * y+x;
			sf::Sprite* rs= new sf::Sprite();				
			rs->setTexture(*TextureList->at(0),true);

			int X1 = x * 32 - y * 32 + (400-32);
			int Y1 = x * 16 + y * 16;
			rs->setPosition(X1,Y1);

			listSprite.push_back(rs);
		}
}


myMap::~myMap(void)
{
}


unsigned char myMap::GetValue(int x, int y)
{
	return width*y +x;
}

void myMap::SetValue(int x, int y, unsigned char val)
{
	map[width*y+x] = val;
	if (val > 0)
	{
		listSprite[width*y+x]->setTexture(*TextureList->at(1),true);
	}
	else
	{
		listSprite[width*y+x]->setTexture(*TextureList->at(0),true);
	}

}

bool myMap::CellIsEmpty(int x,int y) const
{
	if(( x < 0) || (y < 0))
	{
		return false;
	}

	if(( x >= width) || (y >= height))
	{
		return false;
	}

	if( map[width *y +x] == 0)
	{
		return true;
	}

	return false;
}

void myMap::Render(sf::RenderWindow* window)
{
	sf::Vector2u size =  window->getSize();
	for(unsigned int i=0; i < listSprite.size(); i++)
	{
		window->draw(*listSprite[i]);
	}


}