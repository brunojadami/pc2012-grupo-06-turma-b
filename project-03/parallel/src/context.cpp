#include "context.h"

/**
 * @param rank Rank of the process.
 * @param procs Number of processes.
 * @param range Number of x to calculate.
 * @param n Dimension of the A matrix.
 * @param row Row to get the answer.
 * @param iMax Maximum iterations.
 * @param a Matrix A.
 * @param b Vector B.
 * @param x Vector X.
 * @param x_ Vector X_, the working X vector.
 * @param error The error value.
 */
Context::Context(int rank, int procs, int range, int n, int row, int iMax, double* a, double* b, double* x, double* x_, double error)
{
	this->rank = rank;
	this->procs = procs;
	this->range = range;
	this->n = n;
	this->row = row;
	this->iMax = iMax;
	this->a = a;
	this->b = b;
	this->x = x;
	this->x_ = x_;
	this->error = error;
}

/**
 */
Context::~Context()
{
	delete a;
	delete x;
	delete x_;
	delete b;
}
