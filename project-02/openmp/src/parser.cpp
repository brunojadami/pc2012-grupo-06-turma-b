#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;


int isPunct(char c) {
	string punctuation = "\";,.:!?'()[]{}-*";
	if (punctuation.find(c, 0) != -1) return 1;
	return 0;
}

void readSmall()
{
	string s;
	ifstream small("shakespe.txt");
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
		cout << s << endl;

	}
}

void readBig()
{
	string s;
	ifstream big("wikipedia.txt");
	if(!big)
	{
		cout << "Error opening file." << endl;
		exit(-1);

	}
	while(!big.eof())
	{
		getline(big, s);
		s.erase(remove_if(s.begin(), s.end(), isPunct), s.end());
		s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		cout << s << endl;

	}
}


int main() {
	readSmall();
	readBig();
	return 0;
}

