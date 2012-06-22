#ifndef RANDOM_H
#define RANDOM_H

/**
 * Congruential linear generator.
 */
struct Random
{
	Random();
	int next();
	void seed();
	
	int x;
};

#endif
