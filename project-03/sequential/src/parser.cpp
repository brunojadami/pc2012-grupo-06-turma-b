#include "parser.h"
#include <cstdio>
#include <cstring>

/**
 * Read the context variables.
 * @param n Dimension of the A matrix.
 * @param row Row to get the answer.
 * @param error Error value.
 * @param iMax Maximum number of iterations.
 */
void readInput(int& n, int& row, double& error, int& iMax)
{
	scanf("%d", &n);
	scanf("%d", &row);
	scanf("%lf", &error);
	scanf("%d", &iMax);
}

/**
 * @param n Size.
 * @return A double array of size n.
 */
double* createM(int n)
{
	double* m = new double[n];
	return m;
}

/**
 * @param n Size.
 * @return A double array of size n with values read from the input.
 */
double* readM(int n)
{
	double* m = createM(n);
	
	for (int i = 0; i < n; ++i)
	{
		scanf("%lf", &m[i]);
	}
	
	return m;
}

/**
 * @param m Array to clone.
 * @param n Size.
 * @return The array cloned.
 */
double* cloneM(double* m, int n)
{
	double* m_ = new double[n];
	memcpy(m_, m, n * sizeof(double));
	return m_;
}

/**
 * @param m Array to copy.
 * @param d Destination.
 * @param n Size.
 */
void copyM(double* m, double* d, int n)
{
	memcpy(d, m, n * sizeof(double));
}


