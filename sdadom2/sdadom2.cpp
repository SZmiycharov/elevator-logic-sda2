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
#include "ElevatorSequenceQueue.h"

using namespace std;

int findTameTakenBetweenFloors(int lastFloor, int currentFloor, int delay)
{
	return(abs(currentFloor - lastFloor)*5 + delay);
}

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
	PriorityQueue<string> elevatorCourse;

	elevatorCourse.Enqueue("a");
	elevatorCourse.Enqueue("a");
	elevatorCourse.Enqueue("a");
	elevatorCourse.Enqueue("a");
	elevatorCourse.Enqueue("a");
	elevatorCourse.Enqueue("a");
	elevatorCourse.Enqueue("a");
	elevatorCourse.Enqueue("a");
	elevatorCourse.Enqueue("a");


	system("pause");
	return 0;


	ElevatorSequenceQueue test;

	string directions[2] = { "up", "down" };

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

	string lastStop;
	string currentStop;
	int lastStopFloor = 0;
	int currentStopFloor;
	string currentCommandElements[] = { "", "", "", "" };
	int timeTakenBetweenFloors = 0;
	int delay = 0;
	int currentStopTime;
	int lastStopTime = 0;

	while (!elevatorCourse.isEmpty())
	{
		string currentStop = elevatorCourse.Dequeue();
		splitStringToArray(currentStop, ' ', currentCommandElements);

		if (currentCommandElements[1] != directions[0] && currentCommandElements[1] != directions[1])
		{
			assert(istringstream(currentCommandElements[1]) >> currentStopFloor);
			assert(istringstream(currentCommandElements[2]) >> currentStopTime);
		}
		else
		{
			assert(istringstream(currentCommandElements[2]) >> currentStopFloor);
			assert(istringstream(currentCommandElements[3]) >> currentStopTime);
		}

		timeTakenBetweenFloors = findTameTakenBetweenFloors(lastStopFloor, currentStopFloor, currentStopTime-lastStopTime);

		string currentOutput = to_string(timeTakenBetweenFloors) + " " + to_string(currentStopFloor);

		if (currentStopFloor > lastStopFloor)
		{
			currentOutput += " ";
			currentOutput += directions[0];
		}
		else
		{
			currentOutput += " ";
			currentOutput += directions[1];
		}

		//elevatorCourse.findElementBetweenFloorsAndTime(test, currentStopFloor, currentStopTime, lastStopFloor);
		cout << "here";
		return 0;
		while (!test.isEmpty())
		{
			cout << "HERE: " << test.Dequeue() << endl;
		}

		system("pause");
		return 0;



		cout << currentOutput << endl;

		lastStop = currentStop;
		lastStopFloor = currentStopFloor;
		lastStopTime = currentStopTime;
	}

	return 0;
}

