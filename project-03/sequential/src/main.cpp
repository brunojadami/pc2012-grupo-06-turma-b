#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

// Matrixes and vectors
double mat[4000][4000];
double x[4000], xaux[4000];
double b[4000];
// Number of lines and columns, line to inspect, max iterations and total iterations
int n, f, it, rit;
// Error
double err;

/**
 * Load the input and initialize the variables.
 */
void init()
{
	scanf("%d%d%lf%d", &n, &f, &err, &it);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			scanf("%lf", &mat[i][j]);
	for (int i = 0; i < n; ++i)
		scanf("%lf", &b[i]);
	for (int i = 0; i < n; ++i)
	{
		double div = mat[i][i];
		for (int j = 0; j < n; ++j)
			mat[i][j] /= div;
		b[i] /= div;
	}
	for (int i = 0; i < n; ++i)
		x[i] = b[i];
}

/**
 * Check whether the error is enough to stop the method.
 * @return If the error is enough
 */
bool error()
{
	double top = -1/0.0;
	double bot = -1/0.0;
	for (int i = 0; i < n; ++i)
		top = max(top, fabs(xaux[i]-x[i])),
		bot = max(bot, fabs(xaux[i]));
	return top/bot < err;
}

/**
 * The method itself, it solves the linear problem using the Jacobi-Richardson method.
 */
void solve()
{
	bool s = false;
	for (rit = 0; rit < it && !s; ++rit)
	{
		for (int i = 0; i < n; ++i)
		{
			xaux[i] = b[i];
			for (int j = 0; j < n; ++j)
			{
				if (i == j) continue;
				xaux[i] -= x[j]*mat[i][j];
			}
		}
		if (error()) s = 1;
		for (int i = 0; i < n; ++i)
			x[i] = xaux[i];
	}
}

/**
 * Printing the inspected line result and number of iterations.
 */
void print()
{
	printf("Iterations: %d\n", rit);
	double res = 0;
	for (int i = 0; i < n; ++i)
		res += mat[f][i]*x[i];
        printf("Row test: %d => [%lf] =? %lf\n", f, res, b[f]);
}

/**
 * Main function.
 */
int main()
{
	init();
	solve();
	print();
	return 0;
}