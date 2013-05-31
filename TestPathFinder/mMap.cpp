#include "mMap.h"
#include <cstring>


mMap::mMap(int width, int height)
{
	this->width = width;
	this->height = height;
	map = new unsigned char [width * height];
	memset(map,0,width * height);
}


mMap::~mMap(void)
{
	delete map;
}

unsigned char mMap::GetValue(int x, int y)
{
	return width *y +x;
}

void mMap::SetValue(int x, int y, unsigned char val)
{
	map[width *y +x] = val;
}

bool mMap::CellIsEmpty(int x,int y) const
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