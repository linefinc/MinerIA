#include <cstdio>
#include <cstdlib>
#include <memory>

#include "Miner.h"

using namespace std;

int main()
{

	shared_ptr<Miner> pMiner(new Miner(10));
	
	for(int i = 0; i< 2000; i++)
	{
		pMiner->Update();
	}

	getchar();
	return 0;
}