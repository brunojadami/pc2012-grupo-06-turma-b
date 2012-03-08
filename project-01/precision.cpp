#include <cstdio>

/**
 * Main.
 */
int main()
{
	// Counter for precision. It starts at -3 to ignore the 3. and \n.
	long long c = -3;
	
	char aux;
	
	while (scanf("%c", &aux) != EOF)
	{
		c++;
		
		// Each iteration result is printed in one line.
		if (aux == '\n')
		{
			// Prints the line result precision.
			printf("%lld\n", c);
			c = -3;
		}
	}

	return 0;
}
