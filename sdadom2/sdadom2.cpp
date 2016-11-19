/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Stanislav Zmiycharov
* @idnumber 61883
* @task 2
* @compiler VC
*
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>
#include <stdlib.h>
#include "PriorityQueue.h"

using namespace std;

int main(int argc, char* argv[])
{
	PriorityQueue<int> x;
	x.Enqueue(2, 155);
	x.Enqueue(3, 21);
	x.Enqueue(4, 1);
	x.Enqueue(5, 5);
	x.Enqueue(6, 1);

	while (!x.isEmpty())
	{
		cout << x.Dequeue() << endl;
	}

	system("pause");
	return 0;

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

