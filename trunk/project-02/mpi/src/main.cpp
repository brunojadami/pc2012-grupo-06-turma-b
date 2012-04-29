#include <mpi.h>
#include "comm.h"
#include "palindrome.h"
#include "sieve.h"

void mainMaster();

int main(int argc, char** argv) 
{
	int rank, procs;

	MPI_Init(&argc, &argv);
	
	MPI_Comm_size(MPI_COMM_WORLD, &procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (procs < TOTAL_RANKS)
	{
		if (rank == MAIN_MASTER_RANK)
		{
			printf("Not enough threads to start! Needed: %d\n", TOTAL_RANKS);
		}
		
		MPI_Finalize();
	}
	
	if (rank == MAIN_MASTER_RANK)
	{
		mainMaster();
	}
	else if (rank == SIEVE_MASTER_RANK)
	{
		sieveMaster();
	}
	else if (rank >= SIEVE_SLAVES_RANK_START && rank < SIEVE_SLAVES_RANK_START + SIEVE_SLAVES_COUNT)
	{
		sieveSlave();
	}
	else if (rank == PALINDROME_MASTER_RANK)
	{
		palindromeMaster();
	}
	else if (rank >= PALINDROME_SLAVES_RANK_START && rank < PALINDROME_SLAVES_RANK_START + PALINDROME_SLAVES_COUNT)
	{
		palindromeSlave();
	}

	MPI_Finalize();
	
	return 0;
}

void mainMaster()
{
	char buffer[1000];
	MPI_Status status;
	bool loop = true;
	bool smallDone = false;
	bool bigDone = false;
	
	while (loop)
	{
		MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		MPI_Recv(&buffer, status._count, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		
		if (status.MPI_TAG == TAG_FINISH)
		{
			smallDone = smallDone || status.MPI_SOURCE == PARSER_SMALL_RANK;
			bigDone = bigDone || status.MPI_SOURCE == PARSER_BIG_RANK;
		}
		
		if (smallDone && bigDone)
		{
			MPI_Send(buffer, 1, MPI_CHAR, SIEVE_MASTER_RANK, TAG_FINISH, MPI_COMM_WORLD);
			MPI_Send(buffer, 1, MPI_CHAR, PALINDROME_MASTER_RANK, TAG_FINISH, MPI_COMM_WORLD);
		}
	}
}
