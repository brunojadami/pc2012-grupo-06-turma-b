#include <cstdio>
#include <cstring>
#include "palindrome.h"

/**
 * Main (temporary).
 * @return
 */
int main()
{
	char word[10000000];
	
	while (scanf("%s", word) != EOF)
	{
		updatePalindromesCount(word, strlen(word), false);
	}
	
	printf("%d\n", getWordsCount());
	printf("%d\n", getPhrasesCount());
	printf("%d\n", getPrimesCount());
	 
	return 0;
}
