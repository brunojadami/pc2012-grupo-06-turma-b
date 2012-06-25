#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <pthread.h>
#include "random.h"
#include "info.h"
#include "runner.h"

using namespace std;

#define TOTAL_HASH 11881376 // 26^5

int id = 0, left = 0;
Info words[NUM_WORDS];
vector<InfoSet> hash[MAX_WORD_LEN][TOTAL_HASH]; 
int hashCount[MAX_WORD_LEN][TOTAL_HASH]; // Initialized with 0.
pthread_t threads[THREADS];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* function(void* arg)
{
	Random r;
	r.seed();
	
	while (left)
	{
		int num = r.next();
		int use = num;
		int mod = TOTAL_HASH;
		for (int i = MAX_WORD_LEN-1; i >= 0; --i)
		{
			use %= mod;
			mod /= 26;
			if (hashCount[i][use] != 0)
			{
				pthread_mutex_lock(&lock);
				if (hashCount[i][use] != 0)
				{
					hashCount[i][use]--;
					left--;
					InfoSet s = hash[i][use][hashCount[i][use]];
					words[s.id].mask |= s.mask;
					if (__builtin_popcount(words[s.id].mask) == words[s.id].len)
					{
						printf("%s\n", words[s.id].str);
						id--;
					}
				}
				pthread_mutex_unlock(&lock);
				break;
			}
		}
	}
	
	return NULL;
}

void hashString(char* str, int len, int id, int b)
{
	int num = 0;
	int use = len > MAX_WORD_LEN ? MAX_WORD_LEN : len;
	for (int i = 0; i < use; ++i)
	{
		num *= 26;
		num += str[i]-'a';
	}
	hash[use-1][num].push_back(InfoSet(id, 1<<b));
	hashCount[use-1][num]++;
	if (len > MAX_WORD_LEN) hashString(str+MAX_WORD_LEN, len-MAX_WORD_LEN, id, b+1);
}

void run(char** in, int range)
{
	srand(time(NULL));
	
	for (int i = 0; i < range; ++i)
	{
		words[id].str = in[i];
		int len = strlen(words[id].str);
		int num = len/MAX_WORD_LEN;
		if (len%MAX_WORD_LEN) ++num;
		words[id].len = num;
		hashString(words[id].str, len, id, 0);
		++id;
		left += num;
	}
	
	for (int i = 0; i < THREADS; ++i)
	{
		pthread_create(&threads[i], NULL, function, NULL);
	}
	
	for (int i = 0; i < THREADS; ++i)
	{
		pthread_join(threads[i], NULL);
	}
}

