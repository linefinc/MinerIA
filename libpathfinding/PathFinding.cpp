
#include "PathFinding.h"


using namespace std;

PathFinder::PathFinder(const FindableMap* pMap, Point2d start, Point2d destination)
{
	this->pMap = pMap;
	this->start = start;
	this->destination = destination;
	this->Counter = 0;
	ClosedSet.clear();
	OpenSet.clear();
	Path.clear();
}

bool PathFinder::calc()
{
	//printf("[%02d]Start Node %d %d\n",Counter ,start.x, start.y );
	//printf("[%02d]Destiantio Node %d %d\n",Counter ,destination.x, destination.y );

	// initialize Open Set
	start.CalcDistance(destination);
	start.dx = 0;
	start.dy = 0;
	OpenSet.push_back(start);

	//initialize loop 
	while (OpenSet.size() > 0)
	{

		// get the lower score Node and set as currenctNode
		int indexLowerScore = GetLowerScoreNodeFromOpenSet();
		Point2d currenctNode = OpenSet[indexLowerScore];

		if (destination == currenctNode)
		{
			ClosedSet.push_back(currenctNode);
			ReconstructPath();
			ClosedSet.clear();
			OpenSet.clear();
			return true;// todo: make the path here
		}


		// remove currentNode from OpenSet
		OpenSet.erase(OpenSet.begin() + indexLowerScore);
		// add currentNode to CloseSet
		ClosedSet.push_back(currenctNode);

		ProcessNeighbor(currenctNode, +1, +1);
		ProcessNeighbor(currenctNode, +1, +0);
		ProcessNeighbor(currenctNode, +1, -1);

		ProcessNeighbor(currenctNode, -1, +1);
		ProcessNeighbor(currenctNode, -1, +0);
		ProcessNeighbor(currenctNode, -1, -1);

		ProcessNeighbor(currenctNode, +0, +1);
		ProcessNeighbor(currenctNode, +0, -1);

		Counter++;
	}

	// if you are here, we don't find a valid path

	return false;
}

void PathFinder::ProcessNeighbor(const Point2d& currenctNode, int dx, int dy)
{
	Point2d newNode(currenctNode.x + dx, currenctNode.y + dy);
	newNode.dx = dx;
	newNode.dy = dy;

	if (pMap->CellIsEmpty(newNode.x, newNode.y) == false)
	{
		// bad node to explore
		ClosedSet.push_back(newNode);
		return;
	}

	if (NodeIsInOpenSet(newNode) == true)
	{
		ClosedSet.push_back(newNode);
		return;;
	}

	if (NodeIsInCloseSet(newNode) == true)
	{
		ClosedSet.push_back(newNode);
		return;
	}

	newNode.CalcDistance(destination);
	OpenSet.push_front(newNode);

	return;
}

bool PathFinder::NodeIsInCloseSet(const Point2d& node) const
{
	for (unsigned int index = 0; index < ClosedSet.size(); index++)
	{
		if (node == ClosedSet[index])
		{
			return true;
		}
	}

	return false;
}


bool PathFinder::NodeIsInOpenSet(const Point2d& node) const
{
	for (unsigned int index = 0; index < OpenSet.size(); index++)
	{
		if (node == OpenSet[index])
		{
			return true;
		}
	}

	return false;
}

int PathFinder::GetLowerScoreNodeFromOpenSet() const
{
	float distanceMin = +999999999.0f; // todo: change with float.MaxValue
	int indexMin = -1;
	for (unsigned int index = 0; index < OpenSet.size(); index++)
	{
		float d = OpenSet[index].distance;
		if (distanceMin > d)
		{
			distanceMin = d;
			indexMin = index;
		}
	}

	return indexMin;
}


void PathFinder::ReconstructPath(void)
{
	int index = FindNodeByCoordinate(destination.x - destination.dx, destination.y - destination.dy);
	while (index != -1)
	{
		Point2d& currenctNode = ClosedSet[index];
		Path.push_back(currenctNode);
		int nextX = currenctNode.x - currenctNode.dx;
		int nextY = currenctNode.y - currenctNode.dy;

		if ((nextX == start.x) && (nextY == start.y))
		{
			break;
		}
		index = FindNodeByCoordinate(nextX, nextY);
	}

	// reverse list here
	unsigned int halfSize = (Path.size() >> 2);
	unsigned int size = Path.size();


	// todo: reverse list here
}

int PathFinder::FindNodeByCoordinate(int x, int y) const
{
	for (unsigned int index = 0; index < ClosedSet.size(); index++)
	{
		if ((ClosedSet[index].x == x) && (ClosedSet[index].y == y))
		{
			return index;
		}
	}

	return -1;
}

void PathFinder::Optimize(void)
{
	vector<Point2d> outPath(Path);
	unsigned int index = 0;

	while ((outPath.size() - 1) > index)
	{
		char dx1 = outPath[index].dx;
		char dy1 = outPath[index].dy;
		char dx2 = outPath[index + 1].dx;
		char dy2 = outPath[index + 1].dy;

		if ((dx1 == dx2) && (dy1 == dy2))
		{
			outPath.erase(outPath.begin() + index);
		}
		else
		{
			index++;
		}
	}
	Path = outPath;
}

void PathFinder::Reverse(void)
{
	vector<Point2d> outPath;
	// reverse order
	for (int index = Path.size() - 1; index > -1; index--)
	{
		outPath.push_back(Path[index]);
	}

	Path = outPath;
}