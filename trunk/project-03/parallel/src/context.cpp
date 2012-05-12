#include "context.h"

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

Context::~Context()
{
	delete a;
	delete x;
	delete x_;
	delete b;
}
