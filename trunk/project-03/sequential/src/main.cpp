#include "parser.h"
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <algorithm>

/**
 * Normalize the A matrix and the B vector.
 */
void createIdentity(int n, double* a, double* b)
{
	for (int i = 0; i < n; ++i)
	{
		double val = a[i * n + i];
		for (int j = 0; j < n; ++j)
		{
			a[i * n + j] /= val;
		}
		b[i] /= val;
	}
}

/**
 * Checks if can stop.
 * @param lastX The last iteration X vector.
 */
int canStop(double* x_, double* x, double error, int n)
{
	bool stop = true;
	int N = 1;
	for (int j = 0; stop && j < n; )
	{
		for (int i = 0; i < N; ++i)
		{
			if (!stop) continue;
			if ((x_[i+j] - x[i+j]) / x_[i+j] > error)
			{
				stop = false;
			}
		}
		j += N;
		N *= 2;
		N = std::min(N, n-j);
	}
	return stop;
}

/**
 * Sets the answer value.
 */
double solve(double* x, double* a, int row, int n)
{
	double answer = 0;
	
	for (int i = 0; i < n; ++i)
	{
		double aux = x[i]*a[row*n + i];
		answer += aux;
	}
	
	return answer;
}



/**
 * Calculates the next X vector (kept on the x_ variable).
 */
double* process(double* a, double* b, double* x, int n)
{		
	double * x_ = createM(n);
	for (int i = 0; i < n; ++i)
	{
		x_[i] = 0;
		for (int j = 0; j < n; ++j)
		{
			if (i == j) continue;
			x_[i] -= x[j] * a[i*n + j];
		}
		x_[i] += b[i];
	}
	return x_;
}




int main(void)
{
	int n;
	int row;
	int iMax;
	double* a;
	double* b;
	double* x;
	double* x_;
	double* lastX;
	double error;
	double answer;
	int i = 0;
	int stop = 0;
	readInput(n, row, error, iMax);
	a = readM(n * n);
	b = readM(n);
	createIdentity(n, a, b);
	x = cloneM(b, n);

	while (stop == 0 && i++ < iMax)
	{
		lastX = cloneM(x_, n);
		//delete[] x_;
		x_ = process(a, b, x, n);
		x = cloneM(lastX, n);
		//delete[] lastX;
		stop = canStop(x_, x, error, n);
	}
	answer = solve(x_, a, row, n);
	printf("Iterations: %d\n", i);
	printf("Row test: %d => [%lf] =? %lf\n", row, answer, b[row]);
	return 0;
}
