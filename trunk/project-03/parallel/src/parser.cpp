#include "parser.h"
#include <cstdio>

void readInput(int& n, int& row, double& error, int& iMax)
{
	scanf("%d", &n);
	scanf("%d", &row);
	scanf("%lf", &error);
	scanf("%d", &iMax);
}

double** readMA(int n)
{
	double** m = new double[n];
	for (int i = 0; i < n; ++i)
	{
		m[i] = new double[n];
	}
	
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			scanf("%lf", &m[i][j]);
		}
	}
}

double* readMB(int n)
{
	double* m = new double[n];
	
	for (int i = 0; i < n; ++i)
	{
		scanf("%lf", &m[i]);
	}
	
	return m;
}

double* cloneB(double* b, int n)
{
	double* b_ = new double[n];
	memcpy(b_, b, n * sizeof(double));
	return b_;
}

