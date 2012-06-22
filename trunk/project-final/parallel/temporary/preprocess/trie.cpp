#include "trie.h"

#include <cstring>

/**
 * Constructor.
 */
Trie::Trie()
{
	gg = 0;
	memset(t, 0, sizeof t);
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
	if (t[c-'a'] == NULL)
		t[c-'a'] = new Trie();
}

/**
 * Tests whether the child exists.
 * @param c the char of the child.
 * @return true if it exists.
 */
bool Trie::hasChild(char c)
{
	return t[c-'a'] != NULL;
}

/**
 * Insert the string on the trie.
 * @param str the string to be inserted.
 * @return true if it was successfully inserted.
 */
bool Trie::insert(const char* str)
{
	if (str[0] == 0) 
	{
		if (!gg) 
		{
			gg = 1;
			return 1;
		}
		return 0;
	}
	createChild(str[0]);
	return t[str[0]-'a']->insert(str+1);
}

/**
 * Tests whether the trie has the word.
 * @param str the word to be found.
 * @return true if it contains.
 */
bool Trie::have(const char* str)
{
	if (str[0] == 0) return gg;
	if (hasChild(str[0])) return t[str[0]-'a']->have(str+1);
	return 0;
}

/**
 * Desalloc all the memory the trie alloced.
 */
void Trie::clean()
{
	for (int i = 0; i < 26; ++i)
	{
		if (hasChild(i+'a')) t[i]->clean();
		delete t[i];
		t[i] = NULL;
	}
}

