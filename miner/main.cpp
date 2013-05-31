#include <cstdio>
#include <cstdlib>

#include "Miner.h"

int main()
{
	Miner* pMiner = new Miner(0);

	for(int i = 0; i< 2000; i++)
	{
		pMiner->Update();
	}

	getchar();
	return 0;
}