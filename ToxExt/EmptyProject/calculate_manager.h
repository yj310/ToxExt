#pragma once
#include <stdlib.h>
#include <random>

class CalcManager
{
public:

	bool pointByPoint(int ax, int ay, int bx, int by)
	{
		if (ax == bx && bx == by)
			return true;

		return false;
	}

	bool pointBySqare(int ax, int ay, int bx, int by, int bsize)
	{
		for (int i = bx; i < bx + bsize; i++)
		{
			for (int j = by; j < by + bsize; j++)
			{
				if (i == ax && j == ay)
				{
					return true;
				}
			}
		}

		return false;
	}

	bool SqareBySqare(int ax, int ay, int asize, int bx, int by, int bsize)
	{
		if ((ax < bx && ax + asize > bx) || (ax < bx + bsize && ax + asize < bx + bsize)
			&& (ay < by && ay + asize > by) || (ay < by + bsize && ay + asize < by + bsize))
		{
			return true;
		}
		return false;
	}

	int getRand(int i)
	{

		int a = timeGetTime();
		srand(timeGetTime() + i * 50);
		int b = rand();
		return b;
	}


};