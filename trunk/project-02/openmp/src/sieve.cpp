#include <cstdio>
#include <cmath>
#include <omp.h>
#include "sieve.h"

const int MAX = PRIME_MAX; // MAX is the last number
bool comp[(MAX>>1)+1];

/**
 * @param i Integer to be tested.
 * @return True if the given integer is prime.
 */
bool isPrime(int i)
{
	if (i == 2) return true;
	if (i&1) return !comp[i>>1];
	return false;
}

/**
 * Sieve only for odd numbers, handle even and less than 3 on your own..
 */
void sieve()
{
        for (int i = 3; i*i <= MAX; i += 2) 
        {
                if (!comp[i>>1]) 
                {
                	int k = i<<1;
                	#pragma omp parallel for num_threads(SIEVE_N_THREADS)
                        for (int j = i*i; j <= MAX; j += k) 
                        {
                                comp[j>>1] = 1;
                        }
                }
        }
}

