#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include "palindrome.h"

using namespace std;


int isPunct(char c) {
	string punctuation = "\";,.:!?'()[]{}-*";
	if (punctuation.find(c, 0) != -1) return 1;
	return 0;
}

void readSmall()
{
	string s;
	char * cstr;
	while(!cin.eof())
	{
		cin >> s;
		s.erase(remove_if(s.begin(), s.end(), isPunct), s.end());
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		cstr = new char[s.size()+1];
		strcpy (cstr, s.c_str());
		updatePalindromesCount(cstr, s.size(), false);
	}
}

void readBig()
{
	string s;
	char * cstr;
	while(!cin.eof())
	{
		getline(cin, s);
		s.erase(remove_if(s.begin(), s.end(), isPunct), s.end());
		s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		cstr = new char[s.size()+1];
		strcpy (cstr, s.c_str());
		updatePalindromesCount(cstr, s.size(), false);
	}
}


int main(int argc, char* argv[]) {
	if(!strcmp(argv[1], "small"))
		readSmall();
	else if(!strcmp(argv[1], "big"))
		readBig();
	return 0;
}

