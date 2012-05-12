#include <cstdio>
#include <mpi.h>
#include <omp.h>
#include <stdlib.h>
#include "parser.h"
#include "context.h"

Context* context;

void init();
void finalize();
void createIdentity(int, double*, double*);
int run();
void process(int, int);
int canStop();
void solve();

int main(int argc, char** argv)
{
	MPI_Init(&argc, &argv);
	
	init();
	
	int i = run();
	
	if (context->getRank() == 0)
	{
		solve();
	
		printf("Iterations: %d\n", i);
		printf("Row test: %d => [%lf] =? %lf\n", i, context->getAnswer(), context->getB()[context->getRow()]);
	}
	
	finalize();
	
	MPI_Finalize();
	
	return 0;
}

void init()
{
	int rank;
	int procs;
	int range;
	int n;
	int row;
	int iMax;
	double* a;
	double* b;
	double* x;
	double* x_;
	double error;
	
	MPI_Comm_size(MPI_COMM_WORLD, &procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank == 0)
	{
		readInput(n, row, error, iMax);
		a = readM(n * n);
		b = readM(n);
		x = cloneM(b, n);
		x_ = createM(n);
		
		createIdentity(n, a, b);
		
		if (n % procs != 0)
		{
			printf("Invalid number of processes! Aborting..\n");
			exit(-1);
		}
	}
	
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&row, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&error, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(&iMax, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	range = n / procs;
	
	if (rank != 0)
	{
		a = createM(n * n);
		b = createM(n);
		x = cloneM(b, n);
		x_ = createM(n);
	}
	
	MPI_Bcast(a, n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(b, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	context = new Context(rank, procs, range, n, row, iMax, a, b, x, x_, error);
}

void finalize()
{
	delete context;
}

void createIdentity(int n, double* a, double* b)
{
	#pragma omp parallel for num_threads(4)
	for (int i = 0; i < n; ++i)
	{
		double val = a[i * n + i];
		#pragma omp parallel for num_threads(4)
		for (int j = 0; j < n; ++j)
		{
			a[i * n + j] /= val;
		}
		b[i] /= val;
	}
}

int run()
{
	int stop = 0;
	int i = 0;
	
	while (stop == 0 && i++ < context->getIMax())
	{
		process(context->getRank() * context->getRange(), (context->getRank() + 1) * context->getRange() - 1);
		
		MPI_Allgather(context->getX_() + context->getRank() * context->getRange(), context->getRange(), MPI_DOUBLE, context->getX(), context->getRange(), MPI_DOUBLE, MPI_COMM_WORLD);
		
		if (context->getRank() == 0)
		{
			stop = canStop();
		}
		
		MPI_Bcast(&stop, 1, MPI_INT, 0, MPI_COMM_WORLD);
	}
	
	return i;
}

void process(int lower, int upper)
{

}

int canStop()
{
	return 0;
}

void solve()
{

}

