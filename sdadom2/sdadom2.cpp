// sdadom2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <FILENAME>" << "\n";
		system("pause");
		exit(EXIT_FAILURE);
	}
	cout << argv[1] << endl;

	ifstream fileCommands(argv[1]);
	if (fileCommands.is_open())
	{
		string str;
		while (getline(fileCommands, str))
		{
			cout << str << endl;
		}
	}
	else
	{
		cerr << "Unable to open file " << argv[1] << "\n";
		exit(EXIT_FAILURE);
	}

	return 0;
}

