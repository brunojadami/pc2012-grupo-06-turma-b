#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <iterator>

#include "palindrome.h"

using namespace std;

int isPunct(char c) 
{
	if (isalpha(c)) return 0;
	return 1;
}

void readBig()
{
	string s;
	char * cstr;
	while(!cin.eof())
	{
		cin >> s;
		s.erase(remove_if(s.begin(), s.end(), isPunct), s.end());
		
		if (s.size() == 0)
		{
			continue;
		}
		
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		cstr = new char[s.size()+1];
		strcpy (cstr, s.c_str());
		updatePalindromesCount(cstr, s.size(), true);
		delete cstr;
	}
}

void readSmall()
{
	string s;
	char * cstr;
	while(!cin.eof())
	{
		getline(cin, s);
		stringstream linestream(s);
	    	string word;

	    	while (linestream >> word) 
	    	{
	    		word.erase(remove_if(word.begin(), word.end(), isPunct), word.end());
	    		
	    		if (word.size() == 0)
	    		{
	    			continue;
	    		}
	    		
	    		cstr = new char[word.size()+1];
			strcpy(cstr, word.c_str());
			updatePalindromesCount(cstr, word.size(), false);
			delete cstr;
		}
		
		s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
		s.erase(remove_if(s.begin(), s.end(), isPunct), s.end());
		
		if (s.size() == 0)
		{
			continue;
		}
		
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		cstr = new char[s.size()+1];
		strcpy(cstr, s.c_str());
		updatePalindromesCount(cstr, s.size(), true);
		delete cstr;
	}
}

