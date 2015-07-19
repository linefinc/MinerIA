#pragma once
// std library
#include <vector>
// SFML
#include <SFML\Graphics.hpp>
#include "GameObject.h"

class cResurceManager
{
public:
	cResurceManager(void);
	~cResurceManager(void);

	std::vector<sf::Texture*>* TextureList;

};

