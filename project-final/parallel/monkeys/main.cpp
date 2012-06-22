#include <cstdio>
#include <mpi.h>
#include <string>
#include <cstring>
#include <cstdlib>

// Maximum word size (+1).
#define WORD_SIZE 46

using namespace std;

void init();
char* createArray(int);
char** createArrayList(int);

// Words array.
char** words;
// Range of words, the size of the words array, set on the init.
int range;
// Rank of this run.
int rank;
// Number of MPI hosts.
int hosts;

/**
 * Main.
 * @param argc
 * @param argv
 */
int main(int argc, char** argv)
{
	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &hosts);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        
	init();
	
	MPI_Finalize();

	return 0;
}

/**
 * Reads from the input and builds the words buffers.
 */
void init()
{
	int n;
	char word[WORD_SIZE];
	char* buffer;
	
	if (rank == 0)
	{
		// Reads the number of words.
		scanf("%d", &n);
	}
	
	// Broadcasts the number of words.
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
		
	// The last host must contains all the remaining words.
	range = rank < hosts - 1 ? n / hosts : n - n / hosts * (hosts - 1);
	
	if (rank == 0)
	{
		// Rank 0 contains the entire array.
		words = createArrayList(n);
	
		int i = 0;
		int host = 1;
		// This buffer contains the words to be sent.
		string buffer_;
		
		// Parses the words.
		while (scanf("%s", word) != EOF)
		{
			strcpy(words[i], word);
			
			// Checks if it is the first range, for the first rank (don't need to send).
			if (i < range)
			{
				i++;
				continue;
			}
			
			// Adds the word to the buffer.
			if (buffer_.size() > 0)
			{
				buffer_ += " ";
			}
			buffer_ += words[i];
			
			// Checks if the range is over.
			if ((i + 1) % range == 0 && host != hosts - 1 || (i + 1) == n)
			{
				buffer = createArray(buffer_.size() + 1);
				strcpy(buffer, buffer_.c_str());
			
				// Sends the buffer of words trough MPI.
				MPI_Send(buffer, buffer_.size() + 1, MPI_CHAR, host, 0, MPI_COMM_WORLD);
				
				// Increments the host and clears the buffer.
				host++;
				buffer_ = "";
			}
			
			i++;
		}
	}
	else
	{
		// The other ranks contain only a range of the words.
		words = createArrayList(range);
		
		MPI_Status status;
		MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
		
		buffer = createArray(status._count);
		// Receives the buffer of words.
		MPI_Recv(buffer, status._count, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
		
		int pointer = 0;
		int bytesRead = 0;
		int i = 0;
		
		// Parses the buffer received.
		while (sscanf(buffer + pointer, "%s%n", word, &bytesRead) != EOF)
		{
			strcpy(words[i], word);
			i++;
			pointer += bytesRead;
		}
	}
}

/**
 * Creates an array.
 * @param n Array size.
 */
char* createArray(int n)
{
	return new char[n];
}

/**
 * Creates an array list.
 * @param n List size.
 */
char** createArrayList(int n)
{
	char** list = new char*[n];
	
	for (int i = 0; i < n; ++i)
	{
		list[i] = createArray(WORD_SIZE);
	}
	
	return list;
}
