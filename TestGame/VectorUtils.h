#pragma once

#include <SFML/Graphics.hpp>

class VectorUtils
{
public:


	static float Distance2(const sf::Vector2f a,const sf::Vector2f b)
	{
		return (a.x - a.x) *(b.x - b.x) + (a.y - a.y) * (b.y - b.y);
	}

	static sf::Vector2f& Normalize(const sf::Vector2f vec)
	{
		float d = vec.x *vec.x + vec.y * vec.y;
		return sf::Vector2f(vec.x / d, vec.y/d);
	}
	
};

