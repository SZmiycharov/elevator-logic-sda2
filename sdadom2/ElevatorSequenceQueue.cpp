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
		currentCommand = front->Value;
		cout << "current command here: " << currentCommand << endl;
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

		//cout << "curfloor: " << currentFloor << " beginFloor: " << beginFloor << " endfloor: " << endFloor << endl;
		//cout << "curtime: " << currentTime << " beginTime: " << beginTime << "endtime: " << endTime << endl << endl;

		if (currentFloor > beginFloor && currentFloor < endFloor
			&& endTime > currentTime)
		{
			cout << "HEREE\n\n";
			obj.Enqueue(front->pNext->Value, currentFloor);
			cout << front->pNext->Value << endl;
			//delete front->pNext;
			//front->pNext = front->pNext->pNext;
			--Used;
		}
		emptyStringArray(helper, 4);
		front = front->pNext;
	}

	cout << "front: " <<front->Value << endl;
	cout << "oldfront: " <<  oldFront->Value << endl;
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

bool ElevatorSequenceQueue::DequeueElementsInFloorBeforeTime(int currentFloor, int currentTime)
{
	cout << "floor: " << floor << "outsidefloor: " << currentFloor << endl;
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