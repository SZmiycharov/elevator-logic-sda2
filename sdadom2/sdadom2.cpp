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

void emptyStringArray(string(&arr)[4], int length)
{
	for (int i = 0; i < length; i++)
	{
		arr[i] = "";
	}
}

void splitStringToArray(const string &s, char delimeter, string (&elems)[4]) {
	stringstream ss;
	ss.str(s);
	string item;

	int i = 0;

	while (getline(ss, item, delimeter)) {
		elems[i] = item;
		i++;
	}
}

int main(int argc, char* argv[])
{
	PriorityQueue<int> x;
	x.Enqueue(4,1);
	x.Enqueue(3,1);
	x.Enqueue(1,10);
	x.Enqueue(8,6);
	x.Enqueue(4,2);
	x.Enqueue(6,3);

	while (!x.isEmpty())
	{
		cout << "cur element: " << x.Dequeue() << endl;
	}

	system("pause");
	return 0;

	PriorityQueue<string> elevatorCourse;

	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <FILENAME>" << "\n";
		system("pause");
		exit(EXIT_FAILURE);
	}

	ifstream fileCommands(argv[1]);

	if (fileCommands.is_open())
	{
		string line;
		string splittedCommand[] = {"", "", "", ""};
		int priority;
	
		while (getline(fileCommands, line))
		{
			splitStringToArray(line, ' ', splittedCommand);

			if (splittedCommand[3] != "")
			{
				assert(istringstream(splittedCommand[3]) >> priority);
			}
			else
			{
				assert(istringstream(splittedCommand[2]) >> priority);
			}
			elevatorCourse.Enqueue(line, priority);
			emptyStringArray(splittedCommand, 4);
		}

		fileCommands.close();
	}
	else
	{
		cerr << "Unable to open file " << argv[1] << "\n";
		exit(EXIT_FAILURE);
	}

	while (!elevatorCourse.isEmpty())
	{
		cout << elevatorCourse.Dequeue() << endl;
	}

	return 0;
}

