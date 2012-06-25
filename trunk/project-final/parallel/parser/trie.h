#ifndef TRIE_H
#define TRIE_H

/**
 * Prefix tree.
 */
struct Trie
{
	Trie();
	~Trie();
	
	bool insert(const char*);
	bool have(const char*);
	void clean();
	void createChild(char);
	bool hasChild(char);
	
	bool gg;
	Trie* t[26];
};

#endif
