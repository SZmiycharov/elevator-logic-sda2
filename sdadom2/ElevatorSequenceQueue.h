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
private:
	int floor;
	int time;
public:
	ElevatorSequenceQueue() : PriorityQueue() { }
	void splitStringToArray(const std::string &s, char delimeter, std::string(&elems)[4]);
	std::string findElementBetweenFloorsAndTime();
};

