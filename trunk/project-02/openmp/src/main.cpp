#include <cstdio>
#include <cstring>
#include "palindrome.h"
#include "sieve.h"
#include "parser.h"

#ifdef PALINDROME_MAIN
/**
 * Main.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char** argv)
{
	char word[10000];
	
	while (scanf("%s", word) != EOF)
	{
		updatePalindromesCount(word, strlen(word), false);
	}
	 
	return 0;
}
#endif

#ifdef SIEVE_MAIN
/**
 * Main.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char** argv)
{
	sieve();
	 
	return 0;
}
#endif

#ifdef SMALL_MAIN
/**
 * Main.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char** argv)
{
	sieve();
	readSmall();
	
	printf("Palindromes: %d\nPrimes: %d\n", getPalindromesCount(), getPrimesCount());
	 
	return 0;
}
#endif

#ifdef BIG_MAIN
/**
 * Main.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char** argv)
{
	sieve();
	readBig();
	
	printf("Palindromes: %d\nPrimes: %d\n", getPalindromesCount(), getPrimesCount());
	 
	return 0;
}
#endif

