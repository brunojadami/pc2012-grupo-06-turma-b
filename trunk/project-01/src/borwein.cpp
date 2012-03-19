// Include for GNU MP.
#include <gmpxx.h>
#include <iostream>

// Real precision is ~ PRECISION * 0.3012
#define PRECISION 3320053


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
 * Main.
 */
int main()
{
	// Sets output precision.
	cout.precision(PRECISION);
	
	// Initial values: a0, y0.
	mpf_class ai = mpf_class(6 - sqrt(2)*4, PRECISION);
	mpf_class yi = mpf_class(-1 + sqrt(2), PRECISION);

	// On the iteration, ai will be the next 'a' value, while ai_ will be previous.
	mpf_class ai_;
	mpf_class yi_;
	// Get the number of iterations to achieve 10 million digits precision.
	int j = getIterations(PRECISION);

        for(int i = 0; i < j; i++)
	{
		// Store previous iteration values.
		ai_ = ai;
		yi_ = yi;
		// Calculates yi.
		yi = (1 - sqrt(sqrt(1 - pow(yi_, 4))))/(1 + sqrt(sqrt(1 - pow(yi_, 4))));
		// Calculates ai.
		ai = ai_*pow(1 + yi, 4) - pow(2, 2*i + 3)*yi*(1 + yi + pow(yi, 2));
	}
	// Prints pi.
	cout << 1/ai << endl;
	return 0;
}

