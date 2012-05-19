#include "parser.h"
#include <cstdio>
#include <cstring>

FILE* file;

void openFile()
{
	file = fopen("test.txt", "r"); 
}

void closeFile()
{
	fclose(file);
}

void readInput(int& n, int& row, double& error, int& iMax)
{
	fscanf(file, "%d", &n);
	fscanf(file, "%d", &row);
	fscanf(file, "%lf", &error);
	fscanf(file, "%d", &iMax);
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
		fscanf(file, "%lf", &m[i]);
	}
	
	return m;
}

double* cloneM(double* m, int n)
{
	double* m_ = new double[n];
	memcpy(m_, m, n * sizeof(double));
	return m_;
}

void copyM(double* m, double* d, int n)
{
	memcpy(d, m, n * sizeof(double));
}


