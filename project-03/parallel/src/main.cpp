#include <cstdio>
#include <mpi.h>
#include <omp.h>
#include <stdlib.h>
#include <algorithm>
#include "parser.h"
#include "context.h"

// Number of OpenMP threads.
#define N_THREADS 4

Context* context;

void init();
void finalize();
void createIdentity(int, double*, double*);
int run();
void process();
int canStop(double*);
void solve();

/**
 * Main.
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char** argv)
{
	MPI_Init(&argc, &argv);
	
	init();
	
	int i = run();
	
        // The rank 0 is responsible for offering the answer.
	if (context->getRank() == 0)
	{
		solve();
	
		printf("Iterations: %d\n", i);
		printf("Row test: %d => [%lf] =? %lf\n", context->getRow(), context->getAnswer(), context->getB()[context->getRow()]);
	}
	
	finalize();
	
	MPI_Finalize();
	
	return 0;
}

/**
 * Inits everything.
 */
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
	
	// The rank 0 is responsible to read everything.
	if (rank == 0)
	{
		readInput(n, row, error, iMax);
		a = readM(n * n);
		b = readM(n);
		x_ = createM(n);
		
		createIdentity(n, a, b);
		
		x = cloneM(b, n);
		
		if (n % procs != 0)
		{
			printf("Invalid number of processes! Aborting..\n");
			exit(-1);
		}
	}
	
	// Broadcasts to all processes the context vars.
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&row, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&error, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(&iMax, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	// Calculates the range of 'x' for each process.
	range = n / procs;
	
        // Note that the other ranks (rank != 0) only contains the working area of the vectors.
	if (rank != 0)
	{
		a = createM(range * n);
		b = createM(range);
		x = createM(n);
		x_ = createM(range);
	}
	
	// Scatters the A matrix and the B vector to the processes.
	MPI_Scatter(a, n * range, MPI_DOUBLE, a, n * range, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Scatter(b, range, MPI_DOUBLE, b, range, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	// The X vector is on every process.
	MPI_Bcast(x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	// Creates the context.
	context = new Context(rank, procs, range, n, row, iMax, a, b, x, x_, error);
}

/**
 * Finalizes.
 */
void finalize()
{
	delete context;
}

/**
 * Normalize the A matrix and the B vector.
 */
void createIdentity(int n, double* a, double* b)
{
	#pragma omp parallel for num_threads(N_THREADS)
	for (int i = 0; i < n; ++i)
	{
		double val = a[i * n + i];
		#pragma omp parallel for num_threads(N_THREADS)
		for (int j = 0; j < n; ++j)
		{
			a[i * n + j] /= val;
		}
		b[i] /= val;
	}
}

/**
 * Runs the method.
 */ 
int run()
{
	int stop = 0;
	int i = 0;
	double* buffer;
	
	if (context->getRank() == 0)
	{
		// This buffer is the X vector of the last iteration.
		buffer = createM(context->getN());
	}
	
	while (stop == 0 && i++ < context->getIMax())
	{
		process();
		
		if (context->getRank() == 0)
		{
			// Saves the current X before updating the new iteration X.
			copyM(context->getX(), buffer, context->getN());
		}
		
                // Collects the X vector.
		MPI_Allgather(context->getX_(), context->getRange(), MPI_DOUBLE, context->getX(), context->getRange(), MPI_DOUBLE, MPI_COMM_WORLD);
		
		if (context->getRank() == 0)
		{
			// The rank 0 is responsible for the stop.
			stop = canStop(buffer);
		}
		
		MPI_Bcast(&stop, 1, MPI_INT, 0, MPI_COMM_WORLD);
	}
	
	return i;
}

/**
 * Calculates the next X vector (kept on the x_ variable).
 */
void process()
{		
	#pragma omp parallel for num_threads(N_THREADS)
	for (int i = 0; i < context->getRange(); ++i)
	{
		context->getX_()[i] = 0;
		#pragma omp parallel for num_threads(N_THREADS)
		for (int j = 0; j < context->getN(); ++j)
		{
			// It is not j == i because the vectors are not sparse, they only contains the working area (example: the A matrix is from 0 to range * n).
			if (j == context->getRank() * context->getRange() + i) continue;
			#pragma omp atomic
			context->getX_()[i] -= context->getX()[j] * context->getA()[i * context->getN() + j];
		}
		context->getX_()[i] += context->getB()[i];
	}
}

/**
 * Checks if can stop.
 * @param lastX The last iteration X vector.
 */
int canStop(double* lastX)
{
	bool stop = true;
	for (int i = 0; stop && i < context->getN(); ++i)
	{
		if ((context->getX()[i] - lastX[i]) / context->getX()[i] > context->getError())
		{
			stop = false;
		}
	}
	return stop;
	int N = 1;
	for (int j = 0; stop && j < context->getN(); )
	{
		#pragma omp parallel for num_threads(N_THREADS) shared(stop)
		for (int i = 0; i < N; ++i)
		{
			if (!stop) continue;
			if ((context->getX()[i+j] - lastX[i+j]) / context->getX()[i+j] > context->getError())
			{
				stop = false;
			}
		}
		j += N;
		N *= 2;
		N = std::min(N, context->getN()-j);
	}
	return stop;
}

/**
 * Sets the answer value.
 */
void solve()
{
	double answer = 0;
	
	#pragma omp parallel for num_threads(N_THREADS)
	for (int i = 0; i < context->getN(); ++i)
	{
		double aux = context->getX()[i]*context->getA()[context->getRow() * context->getN() + i];
		#pragma omp atomic
		answer += aux;
	}
	
	context->setAnswer(answer);
}

