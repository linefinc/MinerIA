#pragma once


// interface for path finder
class FindableMap
{
public:
	
	virtual bool CellIsEmpty(int x,int y) const = 0 ;
	
};