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
	ElevatorSequenceQueue allCommands;
	ElevatorSequenceQueue scheduledCommands;

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
			allCommands.Enqueue(line, priority);
			emptyStringArray(splittedCommand, 4);
		}

		fileCommands.close();
	}
	else
	{
		cerr << "Unable to open file " << argv[1] << "\n";
		exit(EXIT_FAILURE);
	}

	scheduledCommands.Enqueue(allCommands.Dequeue());

	string currentDirection[2] = { "up", "down" };
	int targetFloor;
	double currentFloor = 1;
	int i = 0;

	//i - vsqka sekunda
	while (true)
	{	
		i++;
		currentFloor += 0.2;

		// check dali ima zaqvka v scheduled commands za tekushtiq etaj - ako da - execute it!
		
		// check dali ima zaqvka v all commands za tekushtata sekunda - ako da - vkarai q v scheduled commands s prioritet: 
		//prioritet: vreme do tekusht target etaj + vreme ot tekusht target etaj do iskaniq etaj

		if (scheduledCommands.isEmpty()) break;
	}
	

	return 0;
}

