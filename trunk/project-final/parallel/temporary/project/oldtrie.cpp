#include "trie.h"

#include <cstring>
#include <cstdio>

/**
 * Constructor.
 */
Trie::Trie()
{
	memset(t, 0, sizeof t);
	ts = 0;
}

/**
 * Destructor.
 */
Trie::~Trie()
{
	
}

/**
 * Creates a child if it does not exists yet.
 * @param c the char of the child.
 */
void Trie::createChild(char c)
{
	if (t[c] == NULL)
	{
		t[c] = new Trie();
		++ts;
	}
}

/**
 * Deletes a child if it does not exists yet.
 * @param c the char of the child.
 */
void Trie::deleteChild(char c)
{
	if (t[c] != NULL)
	{
		t[c]->clean();
		delete t[c];
		t[c] = NULL;
		--ts;
	}
}



/**
 * Tests whether the child exists.
 * @param c the char of the child.
 * @return true if it extists.
 */
bool Trie::hasChild(char c)
{
	return t[c] != NULL;
}

/**
 * Insert the string on the trie.
 * @param str the string to be inserted.
 * @param root the root of the trie, to rewind if word is greater than MAX_WORD_LEN.
 * @param id the string id.
 * @param p the remaining of the word relative to the MAX_WORD_LEN.
 * @param b the bit to set on the mask.
 */
void Trie::insert(const char* str, Trie* root, int id, int p, int b)
{
	if (str[0] == 0) 
		l.push_back(InfoSet(id, 1<<b));
	else if (p == 0)
	{
		l.push_back(InfoSet(id, 1<<b));
		root->insert(str, root, id, MAX_WORD_LEN, b+1);
	}
	else
	{
		createChild(str[0]-'a');
		t[str[0]-'a']->insert(str+1, root, id, p-1, b);
	}
}

/**
 * Desalloc all the memory the trie alloced.
 */
void Trie::clean()
{
	for (int i = 0; i < 26; ++i)
		deleteChild(i);
	ts = 0;
}

/**
 * Generating the words!!
 */
bool Trie::generate(Info* words, int str, int& id, int& left, pthread_mutex_t& found)
{
	if (!l.empty()) // Found a word!
	{
		InfoSet f = *l.begin();
		l.erase(l.begin());
		if (NUM_THREADS > 1) 
			pthread_mutex_lock(&found);
		words[f.id].mask |= f.mask;
		--left;
		if (__builtin_popcount(words[f.id].mask) == words[f.id].len)
		{
			printf("%s\n", words[f.id].str);
			--id;
		}
		if (NUM_THREADS > 1) 
			pthread_mutex_unlock(&found);
		return emptyLeaf();
	}
	else
	{
		char c = str%26;
		bool ret = false;
		if (hasChild(c))
			ret = t[c]->generate(words, str/26, id, left, found);
		if (ret)
			deleteChild(c);
		return emptyLeaf();
	}
}

/**
 * The first node of the trie generate function.
 */
void Trie::process(Info* words, int str, int& id, int& left, pthread_mutex_t* mutexes, pthread_mutex_t& found)
{
	char c = str%26;
	if (NUM_THREADS > 1) 
		pthread_mutex_lock(&mutexes[c]);
	if (hasChild(c))
	{
		bool ret = t[c]->generate(words, str/26, id, left, found);
		if (ret)
			deleteChild(c);
	}
	if (NUM_THREADS > 1) 
		pthread_mutex_unlock(&mutexes[c]);
}

/**
 * Checking if its an empty leaf.
 * @return true if its an empty leaf.
 */
bool Trie::emptyLeaf()
{
	return ts == 0 && l.empty();
}


