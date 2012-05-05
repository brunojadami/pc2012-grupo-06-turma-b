#include <mpi.h>
#include <cstdio>
#include "palindrome.h"
#include "comm.h"

/**
 * Runs the palindrome algorithm.
 * @param word The word to check.
 * @param s Word size.
 * @param palindrome Will be set to true if the word is a palindrome.
 * @param prime Will be set to true if the sum of the ASCII of the chars is prime.
 */
void runPalindrome(char* word, int s, bool& palindrome, bool& prime)
{
	int sum = 0;
	palindrome = true;
	char buffer[1000];
	MPI_Status status;
	
	for (int i = 0; i < s / 2; ++i)
	{
		sum += (int) word[i] + (int) word[s - i - 1];
		palindrome &= word[i] == word[s - i - 1];
	}
	
	if (s % 2 == 1)
	{
		sum += word[s / 2];
	}
	
	sprintf(buffer, "%d", sum);
	
	MPI_Send(buffer, strlen(buffer), MPI_CHAR, SIEVE_MASTER_RANK, TAG_PRIME_QUESTION, MPI_COMM_WORLD);
	MPI_Recv(buffer, 1, MPI_CHAR, SIEVE_MASTER_RANK, TAG_PRIME_ANSWER, MPI_COMM_WORLD, &status);
	
	// The primality answer is true if the first char of the buffer is 1, 0 otherwise.
	prime = buffer[0] == 1;
}

/**
 * Palindrome master.
 * @param palindromesCount Will be set to the number of palindromes calculated.
 * @param primesCount Will be set to the number of primes calculated.
 */
void palindromeMaster(int& palindromesCount, int&primesCount)
{
	char buffer[5000000];
	MPI_Status status;
	int nextSlave = 0;
	palindromesCount = 0;
	primesCount = 0;
	int slavesRunning = 0;
	bool finish = false;
	
	while (!finish || slavesRunning > 0)
	{
		MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		MPI_Recv(&buffer, status._count, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		
		if (status.MPI_TAG == TAG_KILL && status.MPI_SOURCE == MAIN_MASTER_RANK)
		{
			finish = true;
		}
		else if (status.MPI_TAG == TAG_PALINDROME_DONE && status.MPI_SOURCE >= PALINDROME_SLAVES_RANK_START && status.MPI_SOURCE <
			PALINDROME_SLAVES_RANK_START + PALINDROME_SLAVES_COUNT)
		{
			// The buffer contains the result of the palindrome algorithm.
			// The first char is 1 if a palindrome was computed.
			// The second char is 1 if a prime number was found.
			palindromesCount += buffer[0];
			primesCount += buffer[1];
			
			slavesRunning--;
		}
		else if (status.MPI_TAG == TAG_RUN_PALINDROME && (status.MPI_SOURCE == PARSER_SMALL_RANK || status.MPI_SOURCE == PARSER_BIG_RANK))
		{
			// Primes mmust be updated only with the PARSER_BIG_RANK.		
			int tag = status.MPI_SOURCE == PARSER_BIG_RANK ? TAG_RUN_PALINDROME : TAG_RUN_PALINDROME_NO_PRIMES;
			
			MPI_Send(buffer, status._count, MPI_CHAR, PALINDROME_SLAVES_RANK_START + nextSlave, tag, MPI_COMM_WORLD);
			nextSlave = (nextSlave + 1) % PALINDROME_SLAVES_COUNT;
			
			slavesRunning++;
		}
	}
	
	for (int i = PALINDROME_SLAVES_RANK_START; i < PALINDROME_SLAVES_RANK_START + PALINDROME_SLAVES_COUNT; ++i)
	{
		MPI_Send(buffer, 1, MPI_CHAR, i, TAG_KILL, MPI_COMM_WORLD);
	}
	
	MPI_Send(buffer, 1, MPI_CHAR, MAIN_MASTER_RANK, TAG_PALINDROME_FINISHED, MPI_COMM_WORLD);
}

/**
 * Palindrome slave.
 */
void palindromeSlave()
{
	char buffer[5000000];
	MPI_Status status;
	bool finish = false;
	
	int calls = 0;
	
	while (!finish)
	{
		MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		MPI_Recv(&buffer, status._count, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		
		if ((status.MPI_TAG == TAG_RUN_PALINDROME || status.MPI_TAG == TAG_RUN_PALINDROME_NO_PRIMES) && status.MPI_SOURCE == PALINDROME_MASTER_RANK)
		{
			bool palindrome, prime, updatePrime;
			
			updatePrime = status.MPI_TAG == TAG_RUN_PALINDROME;
			
			runPalindrome(buffer, status._count, palindrome, prime);
			
			// Sets the buffer with the answer.
			// The first char is 1 if a palindrome was computed.
			// The second char is 1 if a prime number was found.
			buffer[0] = palindrome ? 1 : 0;
			buffer[1] = (palindrome && updatePrime && prime) ? 1 : 0;
			
			MPI_Send(buffer, 2, MPI_CHAR, PALINDROME_MASTER_RANK, TAG_PALINDROME_DONE, MPI_COMM_WORLD);
		}
		else if (status.MPI_TAG == TAG_KILL && status.MPI_SOURCE == PALINDROME_MASTER_RANK)
		{
			finish = true;
		}
	}
}

