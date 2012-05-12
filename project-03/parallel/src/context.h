#ifndef CONTEXT_H
#define CONTEXT_H

class Context
{
public:
	Context(int, int, int, int, int, int, double*, double*, double*, double*, double);
	~Context();
	
	int getRank() { return rank; }
	int getProcs() { return procs; }
	int getRange() { return range; }
	int getN() { return n; }
	int getRow() { return row; }
	int getIMax() { return iMax; }
	double* getA() { return a; }
	double* getX() { return x; }
	double* getX_() { return x_; }
	double* getB() { return b; }
	double getError() { return error; }
	double getAnswer() { return answer; }
	double getBi() { return bi; }
	
	void setAnswer(double answer) { this->answer = answer; }
	
private:
	int rank;
	int procs;
	int range;
	int n;
	int row;
	int iMax;
	double* a;
	double* x;
	double* x_;
	double* b;
	double error;
	double answer;
};

#endif
