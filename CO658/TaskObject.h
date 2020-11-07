#pragma once

#include <iostream>

using namespace std;

class TaskObject {
public:
	int priority;
	string task;
	TaskObject(int priority, string task) :priority(priority), task(task) {}
	~TaskObject() {}
	// Overload the "<" operator to sort the priority for the queue
	bool operator< (const TaskObject& rhd) {
		return this->priority < rhd.priority;
	}
};
