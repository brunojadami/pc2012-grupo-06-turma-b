#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

double mat[4000][4000];
double x[4000], xaux[4000];
double b[4000];
int n, f, it, rit;
double err;

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

bool error()
{
	double top = -1/0.0;
	double bot = -1/0.0;
	for (int i = 0; i < n; ++i)
		top = max(top, fabs(xaux[i]-x[i])),
		bot = max(bot, fabs(xaux[i]));
	return top/bot < err;
}

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

void print()
{
	printf("Iterations: %d\n", rit);
	double res = 0;
	for (int i = 0; i < n; ++i)
		res += mat[f][i]*x[i];
        printf("Row test: %d => [%lf] =? %lf\n", f, res, b[f]);
}

int main()
{
	init();
	solve();
	print();
	return 0;
}
