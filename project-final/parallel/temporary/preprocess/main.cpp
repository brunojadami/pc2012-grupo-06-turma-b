#include <cstdio>
#include <climits>
#include <cstring>
#include "trie.h"

using namespace std;

// Counter of words, min length of a valid word, max length of a valid word, expected number of iterations.
int cnt = 0, a = INT_MAX, b = INT_MIN, len, exp = 0;
// Input on scanf, the min length word, the max length word.
char in[100], astr[100], bstr[100];
// The root of the trie.
Trie t;

int main()
{
	// Getting all the words and printing the valids ones.
	while (scanf("%[a-z]", in) == 1)
	{
		len = strlen(in);
		if (a > len)
			a = len, strcpy(astr, in);
		if (b < len)
			b = len, strcpy(bstr, in);
		if (t.insert(in)) 
		{
			exp += len;
			++cnt;
			printf("%s\n", in);
		}
		scanf("%*[^a-z]");
	}
	
	printf("%d words! min and max len are: %d/%d %s/%s\n", cnt, a, b, astr, bstr);
	printf("max expected number of iterations is: %lld\n", exp/5*(long long)11881376);
	
	t.clean();
	
	return 0;
}

