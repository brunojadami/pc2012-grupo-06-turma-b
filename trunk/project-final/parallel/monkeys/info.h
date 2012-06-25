#ifndef INFO_H
#define INFO_H

#define MAX_WORD_LEN 5
#define NUM_WORDS 100000
#define LEN 50 // max word size will be 50

/**
 * Information about the word.
 */
struct Info
{
	int mask;
	int len;
	char* str; 
};

/**
 * Information that a child on the trie holds to set the Info struct.
 */
struct InfoSet
{
	InfoSet(int, int);
	
	int id;
	int mask;
};

#endif
