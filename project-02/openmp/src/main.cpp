#include <cstdio>
#include <cstring>
#include "palindrome.h"

#ifdef PALINDROME_MAIN
/**
 * Main (used to count the average words size).
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char** argv)
{
	char word[10000];
	
	int count = 0;
	int average = 0;
	
	while (scanf("%s", word) != EOF)
	{
		int size = strlen(word);
		
		count++;
		average += size;
	}
	
	printf("%d\n", average / count);
	 
	return 0;
}
#else
/**
 * Main (temporary for tests).
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

