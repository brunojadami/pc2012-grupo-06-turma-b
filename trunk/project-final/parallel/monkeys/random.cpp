#include "random.h"

#include <cstdlib>

// Parameters of the linear random number generator.
#define A 53
#define C 3
#define M 11881376 // 26^5

/**
 * Constructor.
 */
Random::Random()
{
	
}

/**
 * Generates a seed.
 */
void Random::seed()
{
	x = rand()%M; // Random seed using rand() once.
}


/**
 * Generates the next random number.
 */
int Random::next()
{
        return x = (x*A+C)%M;
}

