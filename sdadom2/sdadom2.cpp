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
#include "ElevatorCommandsSequence.h"

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

ElevatorCommandsSequence fillPriorityQueueFromFile(string fileName)
{
	ElevatorCommandsSequence elevatorCourse;

	ifstream fileCommands(fileName);

	if (fileCommands.is_open())
	{
		int priority;
		string line;
		string splittedCommand[] = { "", "", "", "" };

		//first line in file is not needed, as our data structure is dynamic
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
		return elevatorCourse;
	}
	else
	{
		cerr << "Unable to open file " << fileName << "\n";
		exit(EXIT_FAILURE);
	}
}

void configureNextTask(string currentCommandArray[4], int &destinationFloor, int &currentTime,
	double currentFloor, string &direction, string &previousDirection)
{
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

	if (destinationFloor > currentFloor)
	{
		direction = "up";
	}
	else if (destinationFloor < currentFloor)
	{
		direction = "down";
	}
	else
	{
		direction = previousDirection;
	}

	if (direction != "")
	{
		previousDirection = direction;
	}
}

void printOutput(int currentTime, double currentFloor, string direction)
{
	cout << currentTime << " " << currentFloor << " " << direction << endl;
}

void changeFloor(string direction, double &currentFloor)
{
	if (direction == "up")
	{
		currentFloor += 0.2;
	}
	else if (direction == "down")
	{
		currentFloor -= 0.2;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <FILENAME>" << "\n";
		system("pause");
		exit(EXIT_FAILURE);
	}

	//ElevatorCommandsSequence is inherited from a priority queue
	//as i wanted to make sure i get commands ordered by their time
	ElevatorCommandsSequence elevatorCourse = fillPriorityQueueFromFile(argv[1]);

	int lastFloor = 1;
	int currentTime = 0;
	int commandTime = 0;
	int destinationFloor;
	double currentFloor = 1;
	string direction;
	//default direction should be down, e.g call
	string previousDirection = "down";
	string currentCommandArray[4];
	string currentCommand = elevatorCourse.Head();
	
	splitStringToArray(currentCommand, ' ', currentCommandArray);
	configureNextTask(currentCommandArray, destinationFloor, currentTime, currentFloor, direction, previousDirection);

	while (true)
	{
		if (fabs(currentFloor - round(currentFloor)) < 0.000000001)
		{
			//if we can take people from current floor, take them and get rid of their requests
			if (elevatorCourse.DequeueElementsInFloorBeforeTime((int)(currentFloor+0.5), currentTime))
			{				
				printOutput(currentTime, currentFloor, direction);

				//end when we don't have any more requests
				if (elevatorCourse.isEmpty())
				{
					break;
				}

				//get next request
				currentCommand = elevatorCourse.Head();
			
				splitStringToArray(currentCommand, ' ', currentCommandArray);

				configureNextTask(currentCommandArray, destinationFloor, commandTime,
					currentFloor, direction, previousDirection);
			}
		}
		changeFloor(direction, currentFloor);
		
		currentTime += 1;
	}

	system("pause");
	return 0;
}

