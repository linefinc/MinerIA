
#include "PathFinding.h"


using namespace std;

PathFinder::PathFinder(const FindableMap* pMap,Point2d start, Point2d destination)
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


	// initialize Open Set
	start.CalcDistance(destination);
	start.dx = 0;
	start.dy = 0;
	OpenSet.push_back(start);
	
	//initialize loop 
	while(OpenSet.size() > 0)
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
		OpenSet.erase(OpenSet.begin()+indexLowerScore);
		// add currentNode to CloseSet
		ClosedSet.push_back(currenctNode);

		

		printf("[%02d]Current Node %d %d %f\n",Counter ,currenctNode.x, currenctNode.y,currenctNode.distance );
		
		
		ProcessNeighbor( currenctNode, +1,+1);
		ProcessNeighbor( currenctNode, +1,+0);
		ProcessNeighbor( currenctNode, +1,-1);

		ProcessNeighbor( currenctNode, -1,+1);
		ProcessNeighbor( currenctNode, -1,+0);
		ProcessNeighbor( currenctNode, -1,-1);

		ProcessNeighbor( currenctNode, +0,+1);
		ProcessNeighbor( currenctNode, +0,-1);

		Counter++;
	}

	// if you are here, we don't find a valid path
	
	return false;
}

bool PathFinder::ProcessNeighbor(const Point2d& currenctNode, int dx, int dy)
{
	Point2d newNode(currenctNode.x+dx,currenctNode.y+dy);
	newNode.dx = dx;
	newNode.dy = dy;

	if(pMap->CellIsEmpty(newNode.x, newNode.y)== false)
	{
		// bad node to explore
		ClosedSet.push_back(newNode);
		return false;
	}

	if(NodeIsInOpenSet(newNode) == true)
	{
		ClosedSet.push_back(newNode);
		return false;
	}

	if(NodeIsInCloseSet(newNode) == true)
	{
		ClosedSet.push_back(newNode);
		return false;
	}

	newNode.CalcDistance(destination);
	OpenSet.push_front(newNode);

	return true;
}

bool PathFinder::NodeIsInCloseSet(const Point2d& node) const
{
	for(unsigned int index = 0; index < ClosedSet.size(); index++)
	{
		if( node == ClosedSet[index])
		{
			return true;
		}
	}

	return false;
}


bool PathFinder::NodeIsInOpenSet(const Point2d& node) const
{
	for(unsigned int index = 0; index < OpenSet.size(); index++)
	{
		if( node == OpenSet[index])
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
	for(int index = 0; index < OpenSet.size(); index ++)
	{
		float d = OpenSet[index].distance;
		if(distanceMin > d)
		{
			distanceMin = d;
			indexMin = index;
		}
	}

	return indexMin;
}


void PathFinder::ReconstructPath(void)
{
	int index = FindNodeByCoordinate(destination.x - destination.dx,destination.y  - destination.dy);
	while(index != -1)
	{
		Point2d& currenctNode = ClosedSet[index];
		Path.push_back(currenctNode);
		int nextX = currenctNode.x - currenctNode.dx;
		int nextY = currenctNode.y - currenctNode.dy;
		
		if((nextX == start.x)&&(nextY == start.y))
		{
			return;
		}
		index = FindNodeByCoordinate(nextX,nextY);
	}

}

int PathFinder::FindNodeByCoordinate(int x ,int y) const
{
	for(unsigned int index = 0; index < ClosedSet.size(); index++)
	{
		if((ClosedSet[index].x == x) && (ClosedSet[index].y == y))
		{
			return index;
		}
	}

	return -1;
}
