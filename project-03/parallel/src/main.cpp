#include <cstdio>
#include <mpi.h>
#include <omp.h>
#include <stdlib.h>
#include "parser.h"

int n, row, iMax;
double** a;
double* x;
double* x_;
double* b;
double error;

void createIdentity();
int run(int, char**);
void process(int, int);
int canStop();
void solve(double&, double&);

int main(int argc, char** argv)
{
	readInput(n, row, error, iMax);
	a = readMA(n);
	b = readMB(n);
	x = cloneB(b, n);
	x_ = cloneB(b, n);
	
	createIdentity();
	
	int i = run(argc, argv);
	
	double answer, bi;
	solve(answer, bi);
	
	printf("Iterations: %d\n", i);
	printf("Row test: %d => [%lf] =? %lf\n", i, answer, bi);
	
	return 0;
}

void createIdentity()
{
	#pragma omp parallel for num_threads(4)
	for (int i = 0; i < n; ++i)
	{
		double val = a[i][i];
		#pragma omp parallel for num_threads(4)
		for (int j = 0; j < n; ++j)
		{
			a[i][j] /= val;
		}
		b[i] /= val;
	}
}

int run(int argc, char** argv)
{
	int rank, procs;

	MPI_Init(&argc, &argv);
	
	MPI_Comm_size(MPI_COMM_WORLD, &procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (n % procs != 0)
	{
		printf("Invalid number of processes! Aborting..\n");
		exit(-1);
	}
	
	int range = n / procs;
	int stop = 0;
	int i = 0;
	
	while (stop == 0 && i++ < iMax)
	{
		if (rank > 0)
		{
			process(rank * range, (rank + 1) * range - 1);
		}
		
		MPI_Allgather(x_ + rank * range, range, MPI_DOUBLE, x, range, MPI_DOUBLE, MPI_COMM_WORLD);
		
		if (rank == 0)
		{
			stop = canStop();
		}
		
		MPI_Bcast(&stop, 1, MPI_INT, 0, MPI_COMM_WORLD);
	}
	
	MPI_Finalize();
	
	return i;
}

void process(int lower, int upper)
{

}

int canStop()
{
	return 0;
}

void solve(double& answer, double& bi)
{

}

