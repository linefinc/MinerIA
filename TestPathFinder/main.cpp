#include <cstdio>
#include <cstdlib>

#include "PathFinding.h"
#include "mMap.h"

void testPositive(mMap* testMap);
void testNegative(mMap* testMap);

int main()
{
	mMap* testMap = new mMap(10,10);

	testPositive(testMap);
	
	//testNegative(testMap);

	PathFinder* pf = new PathFinder(testMap,Point2d(1,9),Point2d(9,9));
	

	if ((pf->calc())== true)
	{
		printf("Obbiettivo raggiunto");
	}
	else
	{
		printf("fail find path");
	}

	delete pf;

	getchar();
	return 0;
}


void testPositive(mMap* testMap)
{
	testMap->SetValue(1,7,1);
	testMap->SetValue(2,2,1);
	testMap->SetValue(2,3,1);
	testMap->SetValue(2,4,1);
	testMap->SetValue(2,5,1);
	testMap->SetValue(2,6,1);
	testMap->SetValue(2,7,1);
	testMap->SetValue(3,4,1);
	testMap->SetValue(4,4,1);
	testMap->SetValue(5,4,1);
	testMap->SetValue(6,4,1);
	testMap->SetValue(7,4,1);
	testMap->SetValue(7,5,1);
	testMap->SetValue(7,6,1);
	testMap->SetValue(7,7,1);
	testMap->SetValue(7,8,1);
	testMap->SetValue(7,9,1);

	testMap->SetValue(5,0,1);
	testMap->SetValue(5,1,1);
	testMap->SetValue(5,2,1);
}

void testNegative(mMap* testMap)
{
	testMap->SetValue(1,7,1);
	testMap->SetValue(2,2,1);
	testMap->SetValue(2,3,1);
	testMap->SetValue(2,4,1);
	testMap->SetValue(2,5,1);
	testMap->SetValue(2,6,1);
	testMap->SetValue(2,7,1);
	testMap->SetValue(3,4,1);
	testMap->SetValue(4,4,1);
	testMap->SetValue(5,4,1);
	testMap->SetValue(6,4,1);
	testMap->SetValue(7,4,1);
	testMap->SetValue(7,5,1);
	testMap->SetValue(7,6,1);
	testMap->SetValue(7,7,1);
	testMap->SetValue(7,8,1);
	testMap->SetValue(7,9,1);

	testMap->SetValue(5,0,1);
	testMap->SetValue(5,1,1);
	testMap->SetValue(5,2,1);


	// close area
	testMap->SetValue(2,1,1);
	testMap->SetValue(2,2,1);
	testMap->SetValue(2,3,1);
	testMap->SetValue(2,0,1);

}
