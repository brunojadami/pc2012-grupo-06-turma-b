// Include for GNU MP.
#include <gmpxx.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

// Real precision is ~ PRECISION * 0.3012
#define PRECISION 320053


using namespace std;

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
 * Calculates the power of parameter f to parameter op.
 */
mpf_class pow(mpf_class f,unsigned long int op)
{
	mpf_t aux;
	mpf_init2(aux, PRECISION);
	mpf_pow_ui(aux, f.get_mpf_t(), op);
	
	return mpf_class(aux, PRECISION);
}


/**
 * Returns the number of iterations necessary for the precision.
 * The Borwein algorithm converges quartically against 1/pi; that is, each iteration approximately quadruples the number of correct digits.
 */

int getIterations(int precision)
{
	int i = 1;
	
	long long v = 1;
	while (v < precision)
	{
		// On each iteration, power the variable by 4, until it reaches the precision.
		v = v << 2;
		i++;
	}
	
	return i;
}

/**
 * Global scope for the threads.
 */
 
// On the iteration, ai will be the next 'a' value, while ai_ will be previous.
mpf_class ai_;
mpf_class yi_;

// Current iteration.
int i = 0;
// Initial values: a0, y0.
mpf_class ai = mpf_class(6 - sqrt(2)*4, PRECISION);

mpf_class yi = mpf_class(-1 + sqrt(2), PRECISION);


// Integer that keeps the count of how many threads finished.
int iteration;
// Mutex used to the main wait the ends of the threads.
sem_t mutex;
// Mutex used to update the iteration integer.
sem_t itMutex;
// Mutex to wait for Y to be calculated.
sem_t yMutex;

/**
 * End of global scope.
 */

void finalizeIteration()
{
        sem_wait(&itMutex);
        iteration++;
        if (iteration == 2)
        {
                sem_post(&mutex);
        }
        sem_post(&itMutex);
}

/**
 * Calculates ai.
 */
void* calculateA(void*)
{
	ai = ai_*pow(1 + yi, 4) - pow(2, 2*i + 3)*yi*(1 + yi + pow(yi, 2));
        finalizeIteration();
}

/**
 * Calculates yi.
 */
void* calculateY(void*)
{
	yi = (1 - sqrt(sqrt(1 - pow(yi_, 4))))/(1 + sqrt(sqrt(1 - pow(yi_, 4))));
                sem_post(&yMutex);
	finalizeIteration();
}




/**
 * Main.
 */
int main()
{
	// Sets output precision.
	cout.precision(PRECISION);
	
	// Get the number of iterations to achieve 10 million digits precision.
	int j = getIterations(PRECISION);

        for(i; i < j; i++)
	{
		// Store previous iteration values.
		ai_ = ai;
		yi_ = yi;

                iteration = 0;
                sem_init(&mutex, 0, 0);
                sem_init(&yMutex, 0, 0);
                sem_init(&itMutex, 0, 1);

                // Calculates the values for the current iteration using threads.
                pthread_t thread;
                pthread_create(&thread, NULL, calculateY, NULL);
                sem_wait(&yMutex);
                pthread_create(&thread, NULL, calculateA, NULL);
		
                sem_wait(&mutex);
                
                // Must destroy the semaphores.
                sem_destroy(&mutex);
                sem_destroy(&itMutex);

	}
	// Prints pi.
	cout << 1/ai << endl;
	return 0;
}

