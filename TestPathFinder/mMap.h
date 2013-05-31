#pragma once
#include "FindableMap.h"


class mMap: public FindableMap
{
private:
	int width; 
	int height;

public:
	mMap(int weidth, int height);
	~mMap(void);

	unsigned char* map;

	unsigned char GetValue(int x, int y);

	void SetValue(int x, int y, unsigned char val);

	bool CellIsEmpty(int x,int y) const;

};

