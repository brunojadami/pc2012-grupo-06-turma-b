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
#ifdef MAIN
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

