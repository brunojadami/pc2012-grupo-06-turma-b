/**
 * Includes.
 */
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <climits>

/**
 * Defines.
 */
#define T ((LL)RAND_MAX)*(RAND_MAX) // The size of the bounding square.
#define LL long long // Long long alias.
#define M 10000000 // Number of iterations

LL cntr, area, a, b; // Points, points inside circle, random number a, random number b.

/**
 * Main.
 */
int main()
{
	srand(time(NULL)); // Generate seed.
	printf("RAND MAX IS: %d\n", RAND_MAX); // Check the random max value, probably 2^32 -1.
	
	// Monte Carlo loop.
	for (cntr = 0; cntr < M; ++cntr)
	{
		a = rand();
		b = rand();
		if (a*a - T <= -b*b) ++area; // Checking if the point is inside the circle.
	}
	
	printf("%lld\n", area*4); // The way this is calculated is explained on the docs.
	
	return 0;
}

