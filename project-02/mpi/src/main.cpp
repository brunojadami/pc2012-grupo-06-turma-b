#include <mpi.h>
#include <cstdio>
#include "comm.h"
#include "palindrome.h"
#include "sieve.h"
#include "parser.h"

/**
 * Main master.
 */
void mainMaster();

/**
 * Main.
 */
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
		return 0;
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
		int palindromesCount, primesCount;
		palindromeMaster(palindromesCount, primesCount);
		printf("Number of palindromes: %d\nNumber of primes: %d\n", palindromesCount, primesCount);
	}
	else if (rank >= PALINDROME_SLAVES_RANK_START && rank < PALINDROME_SLAVES_RANK_START + PALINDROME_SLAVES_COUNT)
	{
		palindromeSlave();
	}
	else if (rank == PARSER_SMALL_RANK)
	{
		smallParser();
	}
	else if (rank == PARSER_BIG_RANK)
	{
		bigParser();
	}
	
	MPI_Finalize();
	
	return 0;
}

/**
 * Main master.
 */
void mainMaster()
{
	char buffer[1000];
	MPI_Status status;
	bool loop = true;
	bool smallParserDone = false;
	bool bigParserDone = false;
	bool palindromeDone = false;
	
	while (loop)
	{
		MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		MPI_Recv(&buffer, status._count, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		
		if (status.MPI_TAG == TAG_PARSER_FINISHED && (status.MPI_SOURCE == PARSER_SMALL_RANK || status.MPI_SOURCE == PARSER_BIG_RANK))
		{
			smallParserDone = smallParserDone || status.MPI_SOURCE == PARSER_SMALL_RANK;
			bigParserDone = bigParserDone || status.MPI_SOURCE == PARSER_BIG_RANK;
		}
		
		if (smallParserDone && bigParserDone)
		{
			loop = false;
		}
	}
	
	// Sends the kill message to the palindrome master and waits it finalize.
	// The sieve master must be shutted down later because the palindrome slaves may be running and needing it.
	MPI_Send(buffer, 1, MPI_CHAR, PALINDROME_MASTER_RANK, TAG_KILL, MPI_COMM_WORLD);
	MPI_Recv(&buffer, 1, MPI_CHAR, PALINDROME_MASTER_RANK, TAG_PALINDROME_FINISHED, MPI_COMM_WORLD, &status);
	
	// Sends the kill message to the sieve master and waits it finalize.
	MPI_Send(buffer, 1, MPI_CHAR, SIEVE_MASTER_RANK, TAG_KILL, MPI_COMM_WORLD);
	MPI_Recv(&buffer, 1, MPI_CHAR, SIEVE_MASTER_RANK, TAG_SIEVE_FINISHED, MPI_COMM_WORLD, &status);
}
