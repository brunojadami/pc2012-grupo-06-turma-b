/**
 * Includes.
 */
#include <cstdio>
#include <ctime>
#include <climits>

/**
 * Defines.
 */
#define LL long long // Long long alias.
#define M 1000000000 // Number of iterations

LL cntr, area, a, b; // Points, points inside circle, random number a, random number b.
const int A = 1103515245, C = 12345; // Parameters of the linear random number generator.
const LL T = (LL)INT_MAX*INT_MAX; // The bounding position of the outter square.

/**
 * Generates the next random number.
 */
int next(int& x)
{
	return x = x*A+C;
}

/**
 * Main.
 */
int main()
{
	int x = time(NULL); // Seed.
	// Monte Carlo loop.
	for (cntr = 0; cntr < M; ++cntr)
	{
		a = next(x);
		b = next(x);
		if (a*a + b*b <= T) ++area; // Checking if the point is inside the circle.
	}
	
	printf("%lld\n", area*4); // The way this is calculated is explained on the docs.
	
	return 0;
}

