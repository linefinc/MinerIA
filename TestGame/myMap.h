#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "FindableMap.h"

enum cellType
{
	empty = 0x1,
	unwalkable = 0x02,
	wheat = 0x04,
};




class myMap : public FindableMap, public sf::Drawable
{
	class MapItem
	{
	private:
		bool walkable;
		unsigned char wheatLevel;
	public:
		sf::Sprite* sprite;
		int x;
		int y;

		// constructor
		MapItem()
		{
			this->sprite = NULL;
			this->wheatLevel = 0;
			this->walkable = true;
		}

		// constructor with value
		MapItem(int x, int y, bool walkable)
		{
			MapItem();
			this->x = x;
			this->y = y;
			this->walkable = walkable;
		}


	public:
		inline void setWalkable(bool value)
		{
			this->walkable = value;
		}

		inline bool getWalkable(void)const
		{
			return this->walkable;
		}

		inline unsigned char getWheatLevel(void) const
		{
			if (this->walkable == true)
			{
				return this->wheatLevel;
			}
			return 0;
		}

		inline void setWheatLevel(unsigned char &value)
		{
			this->wheatLevel = value;
		}
	};





	int scale;
	// ofset for negative value
	int minX;
	int minY;
	int maxX;
	int maxY;

	unsigned int ScreenWidth;
	// draw implementation used form sfml
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	MapItem* GetCell(int x, int y) const;

	unsigned int getWheatLevel(int x, int y) const;
public:
	myMap(int width, int height, unsigned int ScreenWidth, unsigned int boxSide);
	~myMap(void);

	std::vector<sf::Texture*>* TextureList;


	sf::Texture* GreyTexture;
	sf::Texture* RedTexture;
	sf::Texture* GreenTexture0;
	sf::Texture* GreenTexture1;
	sf::Texture* GreenTexture2;
	sf::Texture* GreenTexture3;
	unsigned int boxSide;


	void Dump(const char* fileName) const;

	std::vector<MapItem>* map;

	void SetValue(int x, int y, bool walkable, unsigned char wheatLevel);

	bool CellIsEmpty(int x, int y) const;

	void AddCell(int x, int y, bool walkable, unsigned char wheatLevel);

	void Update(void);

	void setGridScale(int scale)
	{
		this->scale = scale;
	}

	int getGridScale(void)
	{
		return scale;
	}

	int NearestWheat(sf::Vector2f localPosition, sf::Vector2f* out) const;


	sf::Clock clock; // timer
};

