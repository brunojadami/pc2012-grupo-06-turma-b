// Include for GNU MP.
#include <gmpxx.h>
#include <iostream>
#include <ctime>

// Real precision is ~ PRECISION * 0.3012
#define PRECISION 33200

using namespace std;

/**
 * Gets the current time in nanoseconds.
 */
long long getTime()
{
	timespec t;
	if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t) == 0)
	{
		return t.tv_sec * (long long) 1000000000 + t.tv_nsec;
	}
	return 0;
}

/**
 * Calculates the square root of the parameter f.
 */
mpf_class sqrt(mpf_class f)
{
	mpf_t aux;
	mpf_init2(aux, PRECISION);
	
	mpf_sqrt(aux, f.get_mpf_t());
	
	return mpf_class(aux, PRECISION);
}

/**
 * Returns the number of iterations necessary for the precision.
 * The Gauss-Legendre algorithm has second-order convergent nature, which 
 * essentially means that the number of correct digits doubles with each 
 * step of the algorithm.
 */
int getIterations(int precision)
{
	int i = 1;
	
	long long v = 1;
	while (v < precision)
	{
		// On each iteration, power the variable by 2, until it reaches the precision.
		v = v << 1;
		i++;
	}
	
	return i;
}

/**
 * Main.
 */
int main()
{
	// Sets output precision.
	cout.precision(PRECISION);
	
	// Saves the start time.
	long long startTime = getTime();
	
	// Initial values: a0, b0, t0, p0.
	mpf_class ai = mpf_class(1, PRECISION);
	mpf_class bi = mpf_class(0.707106781, PRECISION);
	mpf_class ti = mpf_class(0.25, PRECISION);
	mpf_class pi = mpf_class(1, PRECISION);
	
	// On the iteration, ai will be the next 'a' value, while ai_ will be previous.
	mpf_class ai_;
	mpf_class bi_;
	mpf_class ti_;
	mpf_class pi_;
	
	int i = getIterations(PRECISION);
	
	while (i-- > 0)
	{
		// Saves the last iteration values.
		ai_ = ai;
		bi_ = bi;
		ti_ = ti;
		pi_ = pi;
		
		// Calculates the values for the current iteration.
		ai = (ai_ + bi_) / 2;
		bi = sqrt(bi_ * ai_);
		ti = ti_ - pi * (ai_ - ai) * (ai_ - ai);
		pi =  2 * pi_;
		
		// Prints the 'pi' value.
		cout << ((ai + bi) * (ai + bi) / (4 * ti)) << endl;
	}
	
	// Prints the time elapsed.
	cout << "time elapsed (ns): " << (getTime() - startTime) << endl;

	return 0;
}
