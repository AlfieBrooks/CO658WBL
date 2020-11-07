#pragma once

#include "TaskObject.h"

using namespace std;

class ToDoQueue {
private:
	int count;
	TaskObject **data;
	int size;
public:
	ToDoQueue(int size) :size(size) {
		data = new TaskObject*[size];
		count = 0;
	}
	~ToDoQueue() {}
	void Insert(TaskObject* taskObject) {
		if (isEmpty() == true) {
			data[count++] = taskObject;
		}
		else {
			int i;
			for (i = (count - 1); i >= 0; i--) {
				if (*taskObject < *data[i]) {
					data[i + 1] = data[i];
				} else {
					break;
				}
			}

			data[i + 1] = taskObject;
			count++;
		}
	}
	TaskObject* Remove() {
		count--;
		return data[count];
	}
	bool isEmpty() {
		return count == 0;
	}
};
