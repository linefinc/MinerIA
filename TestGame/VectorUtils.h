#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

class VectorUtils
{
public:


	inline static const float Distance2(const sf::Vector2f a,const sf::Vector2f b)
	{
		float temp1 = a.x - b.x;
		temp1 *= temp1;
		float temp2 = a.y - b.y;
		temp2 *= temp2;
		return temp1 + temp2;
	}

	inline static const sf::Vector2f Normalize(const sf::Vector2f vec)
	{
		float d = sqrt(vec.x *vec.x + vec.y * vec.y);
		return sf::Vector2f(vec.x/ d, vec.y / d);
	}

	inline static const float Length2(const sf::Vector2f vec)
	{
		float temp = vec.x * vec.x;
		temp += vec.y * vec.y;

		return temp;
	}
	

	inline static const sf::Vector2f ConvertToScreenSpace(int x, int y, int ScreenWidth)
	{
		int X1 = x * 32 - y * 32 + ScreenWidth /2 - 32;
		int Y1 = x * 16 + y * 16;
		return sf::Vector2f(X1,Y1);
	}
};

