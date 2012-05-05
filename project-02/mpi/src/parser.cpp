#include <mpi.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "parser.h"
#include "comm.h"

using namespace std;

int isPunct(char c) 
{
	if (isalpha(c)) return 0;
	return 1;
}

void bigParser()
{
	string s;
	char * cstr;
	char buffer;
	ifstream small("small.in");
	if(!small)
	{
		cout << "Error opening file." << endl;
		exit(-1);
	}
	while(!small.eof())
	{
		small >> s;
		s.erase(remove_if(s.begin(), s.end(), isPunct), s.end());
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		cstr = new char[s.size()+1];
		strcpy (cstr, s.c_str());
		MPI_Send(cstr, s.size(), MPI_CHAR, PALINDROME_MASTER_RANK, TAG_RUN_PALINDROME, MPI_COMM_WORLD);
		delete cstr;
	}
	
	MPI_Send(&buffer, 1, MPI_CHAR, MAIN_MASTER_RANK, TAG_PARSER_FINISHED, MPI_COMM_WORLD);
}

void smallParser()
{
	string s;
	char * cstr;
	char buffer;
	ifstream big("big.in");
	if(!big)
	{
		cout << "Error opening file." << endl;
		exit(-1);
	}
	while(!big.eof())
	{
		getline(big, s);

		s.erase(remove_if(s.begin(), s.end(), isPunct), s.end());
	    	stringstream linestream(s);
	    	string word;

	    	while (linestream >> word) 
	    	{
			cstr = new char[s.size()+1];
			strcpy (cstr, word.c_str());
			MPI_Send(cstr, word.size(), MPI_CHAR, PALINDROME_MASTER_RANK, TAG_RUN_PALINDROME, MPI_COMM_WORLD);
		}
		
		s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		cstr = new char[s.size()+1];
		strcpy (cstr, s.c_str());
		MPI_Send(cstr, s.size(), MPI_CHAR, PALINDROME_MASTER_RANK, TAG_RUN_PALINDROME, MPI_COMM_WORLD);
	}
	
	MPI_Send(&buffer, 1, MPI_CHAR, MAIN_MASTER_RANK, TAG_PARSER_FINISHED, MPI_COMM_WORLD);
}
