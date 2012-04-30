#include "sieve.h"

#include <cstdio>
#include <cmath>
#include <omp.h>

const int MAX = PRIME_MAX; // MAX is the last number
bool comp[(MAX>>1)+1];

/**
 * @param i Integer to be tested.
 * @return True if the given integer is prime.
 */
inline bool isPrime(int i)
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
                	#pragma omp parallel for 
                        for (int j = i*i; j <= MAX; j += k) 
                        {
                                comp[j>>1] = 1;
                        }
                }
        }
}

/*int main()
{
	sieve();
	int res = 0;
	for (int i = 3; i < MAX; i += 2)
		res += !comp[i>>1];
	printf("%d\n", res);
	return 0;
}*/

