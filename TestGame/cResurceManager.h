#pragma once
// std library
#include <vector>
// SFML
#include <SFML\Graphics.hpp>


class cResurceManager
{
public:
	cResurceManager(void);
	~cResurceManager(void);

	std::vector<sf::Texture*>* TextureList;
};

