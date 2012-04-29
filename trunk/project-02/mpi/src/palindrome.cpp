#include <mpi.h>
#include "palindrome.h"
#include "comm.h"

void runPalindrome(char* word, int s, bool& palindrome, bool& prime)
{
	int sum = 0;
	palindrome = true;
	char buffer[1000];
	MPI_Status status;
	
	for (int i = 0; i < s / 2; ++i)
	{
		sum += word[i] + word[s - i - 1];
		palindrome &= word[i] == word[s - i - 1];
	}
	
	sprintf(buffer, "%d", sum);
	
	MPI_Send(&buffer, 1, MPI_CHAR, SIEVE_MASTER_RANK, TAG_PRIME_QUESTION, MPI_COMM_WORLD);
	MPI_Recv(&buffer, 1, MPI_CHAR, SIEVE_MASTER_RANK, TAG_PRIME_QUESTION, MPI_COMM_WORLD, &status);
	
	prime = buffer[0] == 1;
}

void palindromeMaster()
{
	char buffer[1000];
	MPI_Status status;
	int nextSlave = 0;
	int palindromesCount = 0;
	int primesCount = 0;
	int slavesRunning = 0;
	bool finish = false;
	
	while (!finish || slavesRunning > 0)
	{
		MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		MPI_Recv(&buffer, status._count, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		
		if (status.MPI_SOURCE == MAIN_MASTER_RANK)
		{
			finish = true;
		}
		else if (status.MPI_TAG == TAG_RUN_PALINDROME && status.MPI_SOURCE >= PALINDROME_SLAVES_RANK_START && status.MPI_SOURCE <
			PALINDROME_SLAVES_RANK_START + PALINDROME_SLAVES_COUNT)
		{
			palindromesCount += buffer[0];
			primesCount += buffer[1];
			slavesRunning--;
		}
		else if (status.MPI_TAG == TAG_RUN_PALINDROME)
		{
			buffer[0] = status.MPI_SOURCE == PARSER_BIG_RANK ? 1 : 0;
			
			MPI_Send(buffer, 1, MPI_CHAR, PALINDROME_SLAVES_RANK_START + nextSlave, TAG_RUN_PALINDROME, MPI_COMM_WORLD);
			nextSlave = (nextSlave + 1) % PALINDROME_SLAVES_COUNT;
			slavesRunning++;
		}
	}
	
	for (int i = PALINDROME_SLAVES_RANK_START; i < PALINDROME_SLAVES_RANK_START + PALINDROME_SLAVES_COUNT; ++i)
	{
		MPI_Send(buffer, 1, MPI_CHAR, i, TAG_FINISH, MPI_COMM_WORLD);
	}
}

void palindromeSlave()
{
	char buffer[1000];
	MPI_Status status;
	bool finish = false;
	
	while (!finish)
	{
		MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		MPI_Recv(&buffer, status._count, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		
		if (status.MPI_SOURCE == PALINDROME_MASTER_RANK && status.MPI_TAG == TAG_RUN_PALINDROME)
		{
			bool palindrome, prime, updatePrime;
			updatePrime = buffer[0] == 1;
			
			runPalindrome(buffer, status._count, palindrome, prime);
			buffer[0] = palindrome ? 1 : 0;
			buffer[1] = updatePrime && prime ? 1 : 0;
			MPI_Send(buffer, 2, MPI_CHAR, PALINDROME_MASTER_RANK, TAG_RUN_PALINDROME, MPI_COMM_WORLD);
		}
		else if (status.MPI_SOURCE == PALINDROME_MASTER_RANK && status.MPI_TAG == TAG_FINISH)
		{
			finish = true;
		}
	}
}

