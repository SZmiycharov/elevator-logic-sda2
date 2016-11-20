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
#include <assert.h>
#include <exception>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "ElevatorSequenceQueue.h"

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