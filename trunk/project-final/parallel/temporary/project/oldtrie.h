#ifndef TRIE_H
#define TRIE_H

#include <list>
#include <pthread.h>
#include "info.h"

using namespace std;

#define NUM_THREADS 1

/**
 * Prefix tree.
 */
struct Trie
{
	Trie();
	~Trie();
	
	void insert(const char*, Trie*, int, int=MAX_WORD_LEN, int=0);
	void clean();
	void createChild(char);
	bool hasChild(char);
	bool generate(Info*, int str, int&, int&, pthread_mutex_t&);
	void process(Info*, int str, int&, int&, pthread_mutex_t*, pthread_mutex_t&);
	bool emptyLeaf();
	void deleteChild(char);
	
	list<InfoSet> l;
	Trie* t[26];
	int ts;
};

#endif
