#pragma once
#include "FindableMap.h"
#include "Point2d.h"
#include <vector>
#include <deque>

using namespace std;

class PathFinder
{
private:
	unsigned int Counter;
	
	Point2d start;
	Point2d destination;
	const FindableMap* pMap;

	vector<Point2d> ClosedSet;
	deque<Point2d> OpenSet;
	
public:
	PathFinder(const FindableMap* pMap,Point2d start, Point2d destination);

	bool calc();

	vector<Point2d> Path;

private:
	int GetLowerScoreNodeFromOpenSet() const;

	bool ProcessNeighbor(const Point2d& currenctNode, int dx, int dy);

	bool NodeIsInCloseSet(const Point2d& node) const;
	
	bool NodeIsInOpenSet(const Point2d& node) const;

	int FindNodeByCoordinate(int x ,int y) const;

	void ReconstructPath(void);


};