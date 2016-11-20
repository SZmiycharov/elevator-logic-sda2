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

#include <assert.h>
#include <exception>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "ElevatorSequenceQueue.h"

using namespace std;

void ElevatorSequenceQueue::splitStringToArray(const std::string &s, char delimeter, std::string(&elems)[4])
{
	std::stringstream ss;
	ss.str(s);
	std::string item;

	int i = 0;

	while (getline(ss, item, delimeter)) {
		elems[i] = item;
		i++;
	}
}

void ElevatorSequenceQueue::findElementBetweenFloorsAndTime(ElevatorSequenceQueue & obj, int beginFloor, int endFloor,
																int beginTime, int endTime)
{
	string currentCommand;
	string helper[4] = {"", "", "", ""};
	int currentFloor;
	int currentTime;
	Container* oldFront = front;

	while (front->pNext)
	{
		currentCommand = front->pNext->Value;
		splitStringToArray(currentCommand, ' ', helper);
		if (helper[3] != "")
		{
			assert(istringstream(helper[2]) >> currentFloor);
			assert(istringstream(helper[3]) >> currentTime);
		}
		else
		{
			assert(istringstream(helper[1]) >> currentFloor);
			assert(istringstream(helper[2]) >> currentTime);
		}

		if (currentFloor > beginFloor && currentFloor < endFloor
			&& currentTime > beginTime && currentTime < endTime)
		{
			obj.Enqueue(front->pNext->Value, currentFloor);
			front->pNext = front->pNext->pNext;
			delete front->pNext;
			--Used;
		}
		emptyStringArray(helper, 4);
		front = front->pNext;
	}
	front = oldFront;
	oldFront = NULL;
	delete oldFront;
	
}

void ElevatorSequenceQueue::emptyStringArray(string(&arr)[4], int length)
{
	for (int i = 0; i < length; i++)
	{
		arr[i] = "";
	}
}