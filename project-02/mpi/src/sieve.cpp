#include <mpi.h>
#include "sieve.h"
#include "comm.h"

void sieveMaster()
{
	char buffer[1000];
	MPI_Status status;
	bool finish = false;
	
	while (!finish)
	{
		MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		MPI_Recv(&buffer, status._count, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		
		if (status.MPI_TAG == TAG_KILL && status.MPI_SOURCE == MAIN_MASTER_RANK)
		{
			finish = true;
		}
		else if (status.MPI_TAG == TAG_PRIME_QUESTION && status.MPI_SOURCE >= PALINDROME_SLAVES_RANK_START && status.MPI_SOURCE <
			PALINDROME_SLAVES_RANK_START + PALINDROME_SLAVES_COUNT)
		{
			buffer[0] = 1;
			MPI_Send(buffer, 1, MPI_CHAR, status.MPI_SOURCE, TAG_PRIME_ANSWER, MPI_COMM_WORLD);
		}
	}
	
	for (int i = SIEVE_SLAVES_RANK_START; i < SIEVE_SLAVES_RANK_START + SIEVE_SLAVES_COUNT; ++i)
	{
		MPI_Send(buffer, 1, MPI_CHAR, i, TAG_KILL, MPI_COMM_WORLD);
	}
	
	MPI_Send(buffer, 1, MPI_CHAR, MAIN_MASTER_RANK, TAG_SIEVE_FINISHED, MPI_COMM_WORLD);
}

void sieveSlave()
{
	char buffer[1000];
	MPI_Status status;
	bool finish = false;
	
	while (!finish)
	{
		MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		MPI_Recv(&buffer, status._count, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		
		if (status.MPI_TAG == TAG_KILL && status.MPI_SOURCE == SIEVE_MASTER_RANK)
		{
			finish = true;
		}
	}
}
