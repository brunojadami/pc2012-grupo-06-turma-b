#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <list>
#include "trie.h"
#include "random.h"

#define GENERATES 1

Trie t;
int id = 0, left = 0;
Info words[NUM_WORDS];

pthread_t threads[26];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* function(void* arg)
{
	int c = *(int*)arg;
	Random r;
	r.seed();
	while (t.hasChild(c) && !t.t[c]->emptyLeaf())
	{
		int num = r.next();
		if (num%26 != c) continue;
		t.generate(words, num, id, left, lock);
	}
	return NULL;
}

void* function2(void* arg)
{
	int c = *(int*)arg;
	Random r;
	r.seed();
	bool g = 1;
	while (!t.emptyLeaf())
	{
		t.generate(words, r.next(), id, left, lock);
	}
	return NULL;
}

int main()
{
	srand(time(NULL));
	
	int cnt = 0;
	
	while (scanf("%s", words[id].str) == 1)
	{
		int len = strlen(words[id].str);
		int num = len/MAX_WORD_LEN;
		if (len%MAX_WORD_LEN) ++num;
		cnt += len*num;
		words[id].len = num;
		t.insert(words[id].str, &t, id);
		++id;
		left += num;
	}
	
	printf("%d\n", cnt);
	
	int use[26];
	for (int i = 0; i < 1; ++i)
	{
		use[i] = i;
		pthread_create(&threads[i], NULL, function2, &use[i]);
	}
	
	for (int i = 0; i < 1; ++i)
	{
		pthread_join(threads[i], NULL);
	}
	
	t.clean();
	
	return 0;
}

