#pragma once


// interface for path finder
class FindableMap
{
public:
	
	virtual bool CellIsEmpty(int x,int y) const = 0 ;

	virtual void setGridScale(int scale) = 0;

	virtual int getGridScale(void) = 0;
	
};