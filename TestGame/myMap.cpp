#include "myMap.h"


myMap::myMap(int width, int height)
	:width(width),height(height)
{
	map = new unsigned char [width * height];
	memset(map, 0, sizeof(map));

	const int boxSide = 36;

	for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++)
		{
			unsigned int i = width * y+x;
			sf::RectangleShape* rs= new sf::RectangleShape(sf::Vector2f(boxSide, boxSide));				
			rs->setPosition(x*boxSide,y*boxSide);
			rs->setFillColor(sf::Color::Green);
			listShape.push_back(rs);
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
		listShape[width*y+x]->setFillColor(sf::Color::Red);
	}
	else
	{
		listShape[width*y+x]->setFillColor(sf::Color::Green);
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
	for(unsigned int i=0; i < listShape.size(); i++)
	{
		window->draw(*listShape[i]);
	}


}