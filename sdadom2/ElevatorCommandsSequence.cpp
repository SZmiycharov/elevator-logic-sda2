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
#include "ElevatorCommandsSequence.h"

using namespace std;

void ElevatorCommandsSequence::splitStringToArray(const std::string &s, char delimeter, std::string(&elems)[4])
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

void ElevatorCommandsSequence::findElementBetweenFloorsAndTime(ElevatorCommandsSequence & obj, int beginFloor, int endFloor,
																int beginTime, int endTime)
{
	string currentCommand;
	string helper[4] = {"", "", "", ""};
	int currentFloor;
	int currentTime;
	Container* oldFront = front;

	while (front->pNext)
	{
		currentCommand = front->Value;
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

		if (beginTime > endTime)
		{
			int helper = beginTime;
			beginTime = endTime;
			endTime = helper;
		}
		if (beginFloor > endFloor)
		{
			int helper = beginFloor;
			beginFloor = endFloor;
			endFloor = helper;
		}

		if (currentFloor > beginFloor && currentFloor < endFloor
			&& endTime > currentTime)
		{
			obj.Enqueue(front->pNext->Value, currentFloor);
			--Used;
		}
		emptyStringArray(helper, 4);
		front = front->pNext;
	}

	front = oldFront;
	oldFront = NULL;
	delete oldFront;
	
}

void ElevatorCommandsSequence::emptyStringArray(string(&arr)[4], int length)
{
	for (int i = 0; i < length; i++)
	{
		arr[i] = "";
	}
}

bool ElevatorCommandsSequence::DequeueElementsInFloorBeforeTime(int currentFloor, int currentTime)
{
	Container* tempFront = front;
	Container* previous = front;
	Container* oldTempFront = front;

	bool foundElements = false;
	int counter = 0;
	int floor;
	int time;
	string splittedCommand[4];
	bool movePointer = true;

	while (tempFront)
	{
		splitStringToArray(tempFront->Value, ' ', splittedCommand);
		if (splittedCommand[0] == "call")
		{
			assert(istringstream(splittedCommand[2]) >> floor);
			assert(istringstream(splittedCommand[3]) >> time);
		}
		else
		{
			assert(istringstream(splittedCommand[1]) >> floor);
			assert(istringstream(splittedCommand[2]) >> time);
		}
		
		
		if (floor == currentFloor && time <= currentTime)
		{
			foundElements = true;
			if (front == tempFront)
			{
				front = front->pNext;
				delete tempFront;
				tempFront = front;
				movePointer = false;
			}
			else
			{
				previous->pNext = tempFront->pNext;
				oldTempFront = tempFront;
				tempFront = tempFront->pNext;
				delete oldTempFront;
				movePointer = false;
			}
		}

		if (movePointer)
		{
			previous = tempFront;
			tempFront = tempFront->pNext;
		}

		movePointer = true;
	}

	tempFront = NULL;
	delete tempFront;
	previous = NULL;
	delete previous;
	oldTempFront = NULL;
	delete oldTempFront;

	return foundElements;
}