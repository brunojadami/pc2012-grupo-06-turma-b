#include <cstdio>
#include <ctime>
#include <cstdlib>
#include "random.h"

int z[11881376];

int main()
{
	// Testing if our random number generator is working properly.
	srand(time(NULL));
	Random r;
	r.seed();
	for (int i = 0; i < 11881376; ++i)
	{
		int s = r.next();
		z[s]++;
		//printf("%d\n", s);
	}
	for (int i = 0; i < 11881376; ++i)
	{
		if (z[i] != 1) printf("%d is not one!\n", i);
	}
	return 0;
}

