#include <mpi.h>
#include <cstring>
#include "parser.h"
#include "comm.h"

/**
 * Big parser.
 */
void bigParser()
{
	char buffer[1000];
	strcpy(buffer, "aasaa");
	
	for (int i = 0; i < 3; ++i)
	{
		MPI_Send(buffer, 1, MPI_CHAR, PALINDROME_MASTER_RANK, TAG_RUN_PALINDROME, MPI_COMM_WORLD);
	}
	
	MPI_Send(buffer, 1, MPI_CHAR, MAIN_MASTER_RANK, TAG_PARSER_FINISHED, MPI_COMM_WORLD);
}

/**
 * Small parser.
 */
void smallParser()
{
	char buffer[1000];
	strcpy(buffer, "aaasaaa");
	
	for (int i = 0; i < 1; ++i)
	{
		MPI_Send(buffer, 1, MPI_CHAR, PALINDROME_MASTER_RANK, TAG_RUN_PALINDROME, MPI_COMM_WORLD);
	}
	
	MPI_Send(buffer, 1, MPI_CHAR, MAIN_MASTER_RANK, TAG_PARSER_FINISHED, MPI_COMM_WORLD);
}

