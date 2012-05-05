#include <mpi.h>
#include <cstring>
#include "parser.h"
#include "comm.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <iterator>

using namespace std;

int isPunct(char c)
{
	string punctuation = "\";,.:!?'()[]{}-*";
	if (punctuation.find(c, 0) != -1) return 1;
	return 0;
}

void readSmall(char * filename)
{
	string s;
	char * cstr;
	ifstream small(filename);
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
		//MPI_Send(cstr, 1, MPI_CHAR, MAIN_MASTER_RANK, TAG_PARSER_FINISHED, MPI_COMM_WORLD);
	}
}

void readBig(char * filename)
{
	string s;
	char * cstr;
	ifstream big(filename);
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

	    	while (linestream >> word) {
			cstr = new char[s.size()+1];
			strcpy (cstr, word.c_str());
			MPI_Send(cstr, 1, MPI_CHAR, MAIN_MASTER_RANK, TAG_PARSER_FINISHED, MPI_COMM_WORLD);
		}
		s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
		transform(s.begin(), s.end(), s.begin(), ::tolower);

		cstr = new char[s.size()+1];
		strcpy (cstr, s.c_str());
		MPI_Send(cstr, 1, MPI_CHAR, MAIN_MASTER_RANK, TAG_PARSER_FINISHED, MPI_COMM_WORLD);


	}
}
