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

class ElevatorSequenceQueue : public PriorityQueue<std::string>
{
public:
	ElevatorSequenceQueue() : PriorityQueue() { }
	void findElementBetweenFloorsAndTime(ElevatorSequenceQueue & obj, int beginFloor, int endFloor, int time);

private:
	void splitStringToArray(const std::string &s, char delimeter, std::string(&elems)[4]);
	
	int floor;
	int time;
};

