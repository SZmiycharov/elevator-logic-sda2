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
#include "PriorityQueue.h"

class ElevatorCommandsSequence : public PriorityQueue<std::string>
{
public:
	ElevatorCommandsSequence() : PriorityQueue() { }
	void findElementBetweenFloorsAndTime(ElevatorCommandsSequence & obj, int beginFloor, int endFloor,
		int beginTime, int endTime);

	bool DequeueElementsInFloorBeforeTime(int currentFloor, int currentTime);

private:
	void splitStringToArray(const std::string &s, char delimeter, std::string(&elems)[4]);
	void emptyStringArray(std::string(&arr)[4], int length);

	int floor;
	int time;
};

