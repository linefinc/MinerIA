#include "myMap.h"
#include "VectorUtils.h"
#include <limits>
#include <cmath>

myMap::myMap(int width, int height, unsigned int ScreenWidth, unsigned int boxSide)// todo: cange coordiante sistem to fit with game coordinte
	:boxSide(boxSide), ScreenWidth(ScreenWidth), scale(1)
{
	map = new std::vector<MapItem>();
	// reset limit
	minX = INT_MAX;
	minY = INT_MAX;
	maxX = INT_MIN;
	maxY = INT_MIN;
	// texure array
	TextureList = new std::vector<sf::Texture*>();


	// load texture from file
	GreyTexture = new sf::Texture();
	GreyTexture->loadFromFile("../data/base/base_0001.png");
	TextureList->push_back(GreyTexture);
	// base RedTexture

	RedTexture = new sf::Texture();
	RedTexture->loadFromFile("../data/base/base_0010.png");
	TextureList->push_back(RedTexture);
	// base 003
	GreenTexture0 = new sf::Texture();
	GreenTexture0->loadFromFile("../data/base/base_0020.png");
	TextureList->push_back(GreenTexture0);
	// 
	GreenTexture1 = new sf::Texture();
	GreenTexture1->loadFromFile("../data/base/base_0021.png");
	TextureList->push_back(GreenTexture1);
	// base 008
	GreenTexture2 = new sf::Texture();
	GreenTexture2->loadFromFile("../data/base/base_0022.png");
	TextureList->push_back(GreenTexture2);
	// todo: fix
	// base 008 
	GreenTexture3 = new sf::Texture();
	GreenTexture3->loadFromFile("../data/base/base_0022.png");
	TextureList->push_back(GreenTexture3);

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			AddCell(x, y, true, 0);
		}


	clock.restart();
}


myMap::~myMap(void)
{
}

//
//	Add cell to Maps
// 
void myMap::AddCell(int x, int y, bool walkable, unsigned char wheatLevel)

{
	if (GetCell(x, y) != NULL)
	{
		return;
	}

	MapItem item(x, y, walkable);
	item.setWheatLevel(wheatLevel);

	item.sprite = new sf::Sprite();
	item.sprite->setPosition(VectorUtils::ConvertToScreenSpace(x, y, ScreenWidth));


	if (walkable == false)
	{
		item.sprite->setTexture(*RedTexture, true);
		return;
	}
	else
	{
		if (wheatLevel == 0)
		{
			item.sprite->setTexture(*GreyTexture, true);
		}
		else
		{
			item.sprite->setTexture(*GreenTexture0, true);
		}

	}

	map->push_back(item);

	// update limit
	if (x < minX)	minX = x;
	if (x > maxX)	maxX = x;
	if (y < minY)	minY = y;
	if (y > maxY)	maxY = y;

}

myMap::MapItem* myMap::GetCell(int x, int y) const
{
	// todo: use more efficient way to scan array
	for (unsigned int index = 0; index < map->size(); index++)
	{
		if ((map->at(index).x == x) && (map->at(index).y == y))
		{
			return &(map->at(index));
		}
	}

	return NULL;
}



void myMap::SetValue(int x, int y, bool walkable, unsigned char wheatLevel)
{
	myMap::MapItem* pItem = GetCell(x, y);

	if (pItem != NULL)
	{
		if (walkable == false)
		{
			pItem->setWalkable(false);
			pItem->sprite->setTexture(*RedTexture, true);
			return;
		}
		else
		{
			pItem->setWalkable(true);
			pItem->setWheatLevel(wheatLevel);
			if (wheatLevel == 0)
			{
				pItem->sprite->setTexture(*GreyTexture, true);
			}
			else
			{
				pItem->sprite->setTexture(*GreenTexture0, true);
			}

		}
	}

}


// Cell Is Empty
// return true if the cell is wolkable
// return flase if the cell is not wolkable
bool myMap::CellIsEmpty(int x, int y) const
{
	if ((x < minX) || (y < minY))
	{
		return false;
	}

	if ((x > maxX) || (y > maxY))
	{
		return false;
	}

	myMap::MapItem* pItem = GetCell(x, y);

	if (pItem != NULL)
	{
		return pItem->getWalkable();
	}
	return false;
}


// Cell Is Empty
// return true if the cell is wolkable
// return flase if the cell is not wolkable
unsigned int myMap::getWheatLevel(int x, int y) const
{
	if ((x < minX) || (y < minY))
	{
		return 0;
	}

	if ((x > maxX) || (y > maxY))
	{
		return 0;
	}

	myMap::MapItem* pItem = GetCell(x, y);

	if (pItem != NULL)
	{
		return pItem->getWheatLevel();
	}

	return 0;
}


void myMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (unsigned int index = 0; index < map->size(); index++)
	{
		if (map->at(index).sprite)
		{
			target.draw(*map->at(index).sprite, states);
		}
	}

}

void myMap::Dump(const char* fileName) const
{
	FILE* fp = NULL;
	if (fopen_s(&fp, fileName, "w") == 0)
	{
		exit(0);
	}

	if (fp == NULL)
	{
		return;
	}
	for (int y = minY; y <= maxY; y++)
	{
		for (int x = minX; x <= maxX; x++)
		{
			myMap::MapItem* pItem = GetCell(x, y);
			if (pItem == NULL)
			{
				fprintf(fp, "X;");
			}
			else
			{
				
				if (pItem->getWalkable() == false)
				{
					fprintf(fp, "W;");
				}

				if (pItem->getWalkable() == true)
				{
					fprintf(fp, "%d;",pItem->getWheatLevel());
				}
			}
		}
		fprintf(fp, "\n");
	}

	fclose(fp);
}

void myMap::Update(void)
{
	if (clock.getElapsedTime().asSeconds() < 1)
	{
		return;
	}
	clock.restart();

	for (int y = minY; y < maxY; y++)
		for (int x = minX; x < maxX; x++)
		{
			myMap::MapItem* pItem = this->GetCell(x, y);

			if (pItem == nullptr)
			{
				continue;
			}

			if (pItem->getWalkable() == true)
			{
				continue;
			}

			// update current cell
			unsigned char wheatLevel = pItem->getWheatLevel();
			if ((++wheatLevel) > 15)
			{
				wheatLevel = 15;
			}
			pItem->setWheatLevel(wheatLevel);


			//////////////////
			//	00	01	02	//
			//	10	XX	12	//
			//	20	21	22	//
			//////////////////
			//myMap::MapItem* pNear;
			//if ((pNear = this->GetCell(x - 1, y - 1)) != nullptr)
			//{
			//	if (pNear->getWalkable() == true)
			//	{
			//		pNear->setWalkable(1);
			//		//pNear->value = cellType::wheat;
			//		goto stop;
			//	}
			//}

			//if ((pNear = this->GetCell(x, y - 1)) != nullptr)
			//{
			//	if (pNear->getWalkable() == true)
			//	{
			//		pNear->setWalkable(1);
			//		//pNear->value = cellType::wheat;
			//		goto stop;
			//	}
			//}

			//if ((pNear = this->GetCell(x + 1, y - 1)) != nullptr)
			//{
			//	if (pNear->getWalkable() == true)
			//	{
			//		pNear->setWalkable(1);
			//		//pNear->value = cellType::wheat;
			//		goto stop;
			//	}

			//}

			//if ((pNear = this->GetCell(x - 1, y)) != nullptr)
			//{
			//	if (pNear->getWalkable() == true)
			//	{
			//		pNear->setWalkable(1);
			//		//pNear->value = cellType::wheat;
			//		goto stop;
			//	}
			//}

			//if ((pNear = this->GetCell(x + 1, y)) != nullptr)
			//{
			//	if (pNear->getWalkable() == true)
			//	{
			//		pNear->setWalkable(1);
			//		//pNear->value = cellType::wheat;
			//		goto stop;
			//	}
			//}

			//if ((pNear = this->GetCell(x - 1, y + 1)) != nullptr)
			//{
			//	if (pNear->getWalkable() == true)
			//	{
			//		pNear->setWalkable(1);
			//		//pNear->value = cellType::wheat;
			//		goto stop;
			//	}
			//}

			//if ((pNear = this->GetCell(x, y + 1)) != nullptr)
			//{
			//	if (pNear->getWalkable() == true)
			//	{
			//		pNear->setWalkable(1);
			//		//pNear->value = cellType::wheat;
			//		goto stop;
			//	}
			//}
			//if ((pNear = this->GetCell(x + 1, y + 1)) != nullptr)
			//{
			//	if (pNear->getWalkable() == true)
			//	{
			//		pNear->setWalkable(1);
			//		//pNear->value = cellType::wheat;
			//		goto stop;
			//	}
			//}

			//		stop:
			if (pItem->getWalkable() == true)
			{
				// update graphics
				if (wheatLevel < 2)	// 0001b	0 - 1  
				{
					pItem->sprite->setTexture(*GreenTexture0, true);
					break;
				}
				if ((wheatLevel > 1) && (wheatLevel < 4))	// 001xb	2 - 3
				{
					pItem->sprite->setTexture(*GreenTexture1, true);
					break;
				}
				if ((wheatLevel > 3) && (wheatLevel < 8))	// 01xxb	4 - 7
				{
					pItem->sprite->setTexture(*GreenTexture2, true);
					break;
				}
				if (wheatLevel > 7) 	// 1xxxb	8 - 15
				{
					pItem->sprite->setTexture(*GreenTexture3, true);
					break;
				}
			}
		}



	//for (unsigned int index = 0; index < map->size(); index++)
	//{
	//	unsigned int wheatLevel = map->at(index).wheatLevel;
	//	if (map->at(index).value == cellType::wheat)
	//	{
	//		myMap::MapItem* pItem = &map->at(index);

	//		// the same of max(15 , wheatLevel+1)
	//		pItem->wheatLevel++;

	//		if (pItem->wheatLevel > 15)
	//		{
	//			pItem->wheatLevel = 15;
	//		}

	//		//// 
	//		//	00	01	02
	//		//	10	XX	12
	//		//	20	21	22
	//		//
	//		if ((pItem->wheatLevel == 0)&(pItem->value == cellType::empty)
	//		{
	//			myMap::MapItem* pNear00 = &map->at(index - maxX - 1);
	//			myMap::MapItem* pNear01 = &map->at(index - maxX + 0);
	//			myMap::MapItem* pNear02 = &map->at(index - maxX + 1);
	//			myMap::MapItem* pNear10 = &map->at(index - 1);
	//			myMap::MapItem* pNear12 = &map->at(index + 1);
	//			myMap::MapItem* pNear20 = &map->at(index + maxX - 1);
	//			myMap::MapItem* pNear21 = &map->at(index + maxX + 0);
	//			myMap::MapItem* pNear22 = &map->at(index + maxX + 1);

	//		}

	//		//int myrand = rand() % 100;
	//		//if (myrand < 50)	// 5 % of probability
	//		//{
	//		//	int x = pItem->x;
	//		//	int y = pItem->y;
	//		//	myrand = (rand() % 3) - 1;	// rand from -1 to 1
	//		//	x += myrand;

	//		//	myrand = (rand() % 3) - 1;	// rand from -1 to 1
	//		//	y += myrand;


	//		//	if (CellIsEmpty(x, y) == true)
	//		//	{
	//		//		int w = GetCell(x, y)->wheatLevel;
	//		//		SetValue(x, y, cellType::wheat, w);
	//		//	}

	//		//}



	//		//
	//		//	Update render
	//		//
	//		if (pItem->wheatLevel < 2)	// 0001b	0 - 1  
	//		{
	//			pItem->sprite->setTexture(*GreenTexture0, true);
	//			break;
	//		}
	//		if ((pItem->wheatLevel > 1) && (pItem->wheatLevel < 4))	// 001xb	2 - 3
	//		{
	//			pItem->sprite->setTexture(*GreenTexture1, true);
	//			break;
	//		}
	//		if ((pItem->wheatLevel > 3) && (pItem->wheatLevel < 8))	// 01xxb	4 - 7
	//		{
	//			pItem->sprite->setTexture(*GreenTexture2, true);
	//			break;
	//		}
	//		if (pItem->wheatLevel > 7) 	// 1xxxb	8 - 15
	//		{
	//			pItem->sprite->setTexture(*GreenTexture3, true);
	//			break;
	//		}
	//}
}


bool myMap::NearestWheat(sf::Vector2f localPosition, sf::Vector2f* out) const
{
	MapItem* bestNode = nullptr;
	float distance2 = INT_MAX;

	for (unsigned int index = 0; index < map->size(); index++)
	{
		printf("here %d %d %d\n", map->at(index).x, map->at(index).y, map->at(index).getWheatLevel());

		if ((map->at(index).getWalkable() == true)&(map->at(index).getWheatLevel() > 0))
		{

			float deltaX = map->at(index).x - localPosition.x;
			float distanceTemp = deltaX * deltaX;
			float deltaY = map->at(index).y - localPosition.y;
			distanceTemp += deltaY*deltaY;

			if (distance2 > distanceTemp)
			{
				distance2 = distanceTemp;
				bestNode = &map->at(index);
			}
		}
	}

	// to do : add error if not exist Wheat
	if (bestNode == nullptr)
	{
		return false;
	}
	out->x = static_cast<float>(bestNode->x);
	out->y = static_cast<float>(bestNode->y);

	return true;
}