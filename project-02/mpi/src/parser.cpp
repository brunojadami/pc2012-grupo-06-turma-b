#include <mpi.h>
#include <cstring>
#include "parser.h"
#include "comm.h"

void bigParser()
{
	char buffer[1000];
	strcpy(buffer, "aasaa");
	
	for (int i = 0; i < 100; ++i)
	{
		MPI_Send(buffer, 1, MPI_CHAR, PALINDROME_MASTER_RANK, TAG_RUN_PALINDROME, MPI_COMM_WORLD);
	}
}

void smallParser()
{
	char buffer[1000];
	strcpy(buffer, "aaasaaa");
	
	for (int i = 0; i < 50; ++i)
	{
		MPI_Send(buffer, 1, MPI_CHAR, PALINDROME_MASTER_RANK, TAG_RUN_PALINDROME, MPI_COMM_WORLD);
	}
}

