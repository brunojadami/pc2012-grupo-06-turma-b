#include "sieve.h"
#include "comm.h"

#include <mpi.h>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

const int MAX = PRIME_MAX;

/**
 * Broadcasting a message.
 */
void broadcast(char* data, int size)
{
	for (int i = 0; i < SIEVE_SLAVES_COUNT; ++i)
	{
		MPI_Send(data, size, MPI_CHAR, i+SIEVE_SLAVES_RANK_START, 0, MPI_COMM_WORLD);
	}
}

/**
 * Sieve master.
 */
void sieveMaster()
{
	int size = SIEVE_SLAVES_COUNT;
	if (size == 0)
	{
		printf("No slaves allocated!\n");
		return;
	}
	if (MAX%size != 0)
	{
		printf("Invalid number of slaves!\n");
		return;
	}
	
	int block = MAX/size;
	MPI_Status status;
	char res;
	for (int i = 3; i*i <= MAX; i += 2)
	{
		int t = (i-1)/block;
		res = 0;
		MPI_Send(&res, 1, MPI_CHAR, SIEVE_SLAVES_RANK_START+t, 0, MPI_COMM_WORLD);
		MPI_Send(&i, 1, MPI_INT, SIEVE_SLAVES_RANK_START+t, 0, MPI_COMM_WORLD);
		MPI_Recv(&res, 1, MPI_CHAR, SIEVE_SLAVES_RANK_START+t, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		
		//printf("%d is %d\n", i, res);
		
		if (res) continue;
		
		res = 1;
		broadcast(&res, 1);
		broadcast((char*)(&i), 4);
	}
	
	char buffer[1000];
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
			// The first char of the buffer answers the primality. 1 means it is prime, 0 means not.
			res = 0;
			int source = status.MPI_SOURCE;
			int i = atoi(buffer);
			int t = (i-1)/block;
			MPI_Send(&res, 1, MPI_CHAR, SIEVE_SLAVES_RANK_START+t, 0, MPI_COMM_WORLD);
			MPI_Send(&i, 1, MPI_INT, SIEVE_SLAVES_RANK_START+t, 0, MPI_COMM_WORLD);
			MPI_Recv(&res, 1, MPI_CHAR, SIEVE_SLAVES_RANK_START+t, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			buffer[0] = res;
			MPI_Send(buffer, 1, MPI_CHAR, source, TAG_PRIME_ANSWER, MPI_COMM_WORLD);
		}
	}
	
	res = 2;
	//printf("finish him!\n");
	broadcast(&res, 1);
}

void sieveSlave()
{
	int rank;
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	int size = SIEVE_SLAVES_COUNT;
	if (size == 0) return;
	if (MAX%size != 0) return;
	
	int block = MAX/size;
	vector<char> comp(block);
	rank -= SIEVE_SLAVES_RANK_START;
	rank++;
	int start = (rank-1)*block+1, end = rank*block;
	if (start == 1) comp[0] = 1;
	//printf("start %d end %d rank %d\n", start, end, rank);
	MPI_Status status;
	
	while (1)
	{
		char opt;
		int i;
		MPI_Recv(&opt, 1, MPI_CHAR, SIEVE_MASTER_RANK, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		//printf("%d received %d\n", rank, opt);
		if (opt == 2) break;
		
		if (opt == 0)
		{
			MPI_Recv(&i, 1, MPI_INT, SIEVE_MASTER_RANK, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			//printf("data is %d\n", i);
			opt = comp[(i-1)%block];
			MPI_Send(&opt, 1, MPI_CHAR, SIEVE_MASTER_RANK, 0, MPI_COMM_WORLD);
		}
		else if (opt == 1)
		{
			MPI_Recv(&i, 1, MPI_INT, SIEVE_MASTER_RANK, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			//printf("%d comp %d\n", rank, i);
			int j = i*i;
			int z = start/i*i;
			if (z < start) z += i;
			int k = i<<1;
			if (z%2 == 0) z += i;
			for (z = max(j, z); z <= end; z += k)
			{
				//printf("comp %d\n", z);
				comp[(z-1)%block] = 1;
			}
		}
	}
	
	/*int cnt = 0;
	for (int i = start%2==0; i < block; i += 2)
	{
		//if (!comp[i]) printf("%d prime\n", i+start);
		cnt += !comp[i];
	}
	printf("got %d primes on %d\n", cnt, rank);*/
}

/*int main (int argc, char *argv[])
{
	int rank, size;

	MPI_Init (&argc, &argv);	
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);	
	MPI_Comm_size (MPI_COMM_WORLD, &size);	
	
	if (rank == 0)
		master(size);
	else
		slave(rank, size);
	
	MPI_Finalize();
	return 0;
}*/

