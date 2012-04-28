#include <omp.h>
#include "palindrome.h"
#include "crivo.h"

// Words that are palindromes.
int wordsCount = 0;
// Phrases that are palindromes.
int phrasesCount = 0;
// Palindromes with the sum of characters that results on a prime number.
int primesCount = 0;

/**
 * @param word Word.
 * @param s Word size.
 * @param isPhrase If true, the word is a phrase instead. In this case, the prime numbers aren't updated.
 */
void updatePalindromesCount(char* word, int s, bool isPhrase)
{
	int i;
	int sum = 0;
	bool palindrome = true;
	
	#pragma omp parallel for num_threads(PALINDROME_N_THREADS) schedule(dynamic, PALINDROME_BLOCK_SIZE) reduction(+:sum) reduction(&&:palindrome)
	for (i = 0; i < s / 2; ++i)
	{
		sum += word[i] + word[s - i - 1];
		palindrome &= word[i] == word[s - i - 1];
	}
	
	if (isPhrase)
	{
		phrasesCount += palindrome ? 1 : 0;
	}
	else
	{
		wordsCount += palindrome ? 1 : 0;
		primesCount += isPrime(sum) ? 1 : 0;
	}
}

/**
 * @return Number of words that are palindromes.
 */
int getWordsCount()
{
	return wordsCount;
}

/**
 * @return Number of phrases that are palindromes.
 */
int getPhrasesCount()
{
	return phrasesCount;
}

/**
 * @return Number of palindromes with the sum of characters that results on a prime number.
 */
int getPrimesCount()
{
	return primesCount;
}

