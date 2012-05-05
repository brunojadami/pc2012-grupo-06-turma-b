#include <omp.h>
#include <cstdio>
#include "palindrome.h"
#include "sieve.h"

// Words that are palindromes (phrases included).
int palindromesCount = 0;
// Palindromes with the sum of characters that results on a prime number.
int primesCount = 0;

/**
 * @param word Word or phrase.
 * @param s Word or phrase size.
 * @param updatePrimeCount If true, the prime numbers are updated.
 */
void updatePalindromesCount(char* word, int s, bool updatePrimeCount)
{
	int i;
	int sum = 0;
	bool palindrome = true;
	
	#pragma omp parallel for num_threads(PALINDROME_N_THREADS) schedule(dynamic, PALINDROME_BLOCK_SIZE) reduction(+:sum) reduction(&&:palindrome)
	for (i = 0; i < s / 2; ++i)
	{
		sum += (int) word[i] + (int) word[s - i - 1];
		palindrome &= word[i] == word[s - i - 1];
	}
	
	if (sum < 0)
	{
		int t = 0;
	}
	
	palindromesCount += palindrome ? 1 : 0;
	primesCount += updatePrimeCount && isPrime(sum) ? 1 : 0;
}

/**
 * @return Number of palindromes.
 */
int getPalindromesCount()
{
	return palindromesCount;
}

/**
 * @return Number of palindromes with the sum of characters that results on a prime number.
 */
int getPrimesCount()
{
	return primesCount;
}

