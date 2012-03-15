// Include for GNU MP.
#include <gmpxx.h>
#include <iostream>
#include <ctime>
#include <pthread.h>
#include <semaphore.h>

// Real precision is ~ PRECISION * 0.3012
#define PRECISION 3320053

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
 * Global scope for the threads.
 */
 
// On the iteration, ai will be the next 'a' value, while ai_ will be previous.
mpf_class ai_;
mpf_class bi_;
mpf_class ti_;
mpf_class pi_;
	
// Initial values: a0, b0, t0, p0.
mpf_class ai = mpf_class(1, PRECISION);
mpf_class bi = mpf_class(0.707106781, PRECISION);
mpf_class ti = mpf_class(0.25, PRECISION);
mpf_class pi = mpf_class(1, PRECISION);

// Integer that keeps the count of how many threads finished.
int iteration;
// Mutex used to the main wait the ends of the threads.
sem_t mutex;

/**
 * End of global scope.
 */

/**
 * Tries to finilize the iteration, posting the mutex if all threads finished.
 */
void finalizeIteration()
{
	if (iteration == 3)
	{
		sem_post(&mutex);
	}
}

/**
 * Calculates ai and ti.
 */
void* calculateAT(void*)
{
	ai = (ai_ + bi_) / 2;
	ti = ti_ - pi * (ai_ - ai) * (ai_ - ai);
	iteration++;
	finalizeIteration();
}

/**
 * Calculates bi.
 */
void* calculateB(void*)
{
	bi = sqrt(bi_ * ai_);
	iteration++;
	finalizeIteration();
}

/**
 * Calculates pi.
 */
void* calculateP(void*)
{
	pi =  2 * pi_;
	iteration++;
	finalizeIteration();
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
	
	int i = getIterations(PRECISION);
	
	while (i-- > 0)
	{
		// Saves the last iteration values.
		ai_ = ai;
		bi_ = bi;
		ti_ = ti;
		pi_ = pi;
		
		iteration = 0;
		sem_init(&mutex, 0, 0);
		
		// Calculates the values for the current iteration using threads.
		pthread_t thread;
		pthread_create(&thread, NULL, calculateAT, NULL);
		pthread_create(&thread, NULL, calculateB, NULL);
		pthread_create(&thread, NULL, calculateP, NULL);
		
		sem_wait(&mutex);
		
		// Prints the 'pi' value.
		cout << ((ai + bi) * (ai + bi) / (4 * ti)) << endl;
	}
	
	// Prints the time elapsed.
	cout << "time elapsed (ns): " << (getTime() - startTime) << endl;

	return 0;
}
