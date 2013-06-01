#pragma once
#include <string>

using namespace std;

// generic object
class GameObject
{	
	virtual int GetID() const= 0 ;

	virtual string GetName() const = 0 ; 
};
