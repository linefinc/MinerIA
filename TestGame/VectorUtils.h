#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

class VectorUtils
{
public:


	static float Distance2(const sf::Vector2f a,const sf::Vector2f b)
	{
		float temp1 = a.x - b.x;
		temp1 *= temp1;
		float temp2 = a.y - b.y;
		temp2 *= temp2;
		return temp1 + temp2;
	}

	static sf::Vector2f& Normalize(const sf::Vector2f vec)
	{
		float d = sqrt(vec.x *vec.x + vec.y * vec.y);
		return sf::Vector2f(vec.x/ d, vec.y / d);
	}

	static float Length2(const sf::Vector2f vec)
	{
		float temp = vec.x * vec.x;
		temp += vec.y * vec.y;

		return temp;
	}
	
};

