#include "parser.h"
#include <cstdio>
#include <cstring>

void readInput(int& n, int& row, double& error, int& iMax)
{
	scanf("%d", &n);
	scanf("%d", &row);
	scanf("%lf", &error);
	scanf("%d", &iMax);
}

double* createM(int n)
{
	double* m = new double[n];
	return m;
}

double* readM(int n)
{
	double* m = createM(n);
	
	for (int i = 0; i < n; ++i)
	{
		scanf("%lf", &m[i]);
	}
	
	return m;
}

double* cloneM(double* m, int n)
{
	double* m_ = new double[n];
	memcpy(m_, m, n * sizeof(double));
	return m_;
}

