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
	ElevatorSequenceQueue elevatorCourse;

	string directions[2] = { "up", "down" };
	string directions2[2] = { "up", "down" };

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

		//first line in file is not actually needed
		getline(fileCommands, line);
		
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

	int lastFloor = 1;
	int currentTime = 0;
	int destinationFloor;
	string direction = "up";
	double currentFloor = 1;
	string currentCommandArray[4];
	string currentCommand = elevatorCourse.Dequeue();
	
	splitStringToArray(currentCommand, ' ', currentCommandArray);

	if (currentCommandArray[0] == "call")
	{
		assert(istringstream(currentCommandArray[2]) >> destinationFloor);
		assert(istringstream(currentCommandArray[3]) >> currentTime);
	}
	else
	{
		assert(istringstream(currentCommandArray[1]) >> destinationFloor);
		assert(istringstream(currentCommandArray[2]) >> currentTime);
	}
	cout << direction << endl << endl;

	while (currentTime < 120)
	{

		cout << "time: " << currentTime << "s; floor: " << currentFloor << "; direction: " << direction << endl;

		// check if we are on some floor <like 1, 2, 3 and not 1.2 and 2.3>
		if (fabs(currentFloor - round(currentFloor)) < 0.000001)
		{
			if (elevatorCourse.DequeueElementsInFloorBeforeTime(currentFloor, currentTime))
			{
				cout << "*****************GETTING-PEOPLE: " << currentTime << " " << currentFloor << " " 
					<< direction << "*****************" << endl;

				//get next request
				currentCommand = elevatorCourse.Dequeue();
				cout << "currentcommand: " << currentCommand << endl;

				splitStringToArray(currentCommand, ' ', currentCommandArray);

				if (currentCommandArray[0] == "call")
				{
					assert(istringstream(currentCommandArray[2]) >> destinationFloor);
				}
				else
				{
					assert(istringstream(currentCommandArray[1]) >> destinationFloor);
				}

				if (destinationFloor > currentFloor)
				{
					direction = "up";
				}
				else
				{
					direction = "down";
				}
			}
		}
		
		if (direction == "up")
		{
			currentFloor += 0.2;
		}
		else if (direction == "down")
		{
			currentFloor -= 0.2;
		}
		
		currentTime += 1;
				
	}

	system("pause");
	return 0;
}

