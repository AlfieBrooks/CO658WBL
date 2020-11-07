#pragma once

#include "TaskObject.h"

using namespace std;

// Define the queue size
#define SIZE 20

class ToDoQueue {
private:
	int count;
	TaskObject **data;
public:
	// Constructor to initalise the queue with the size of the size parameter
	ToDoQueue() {
		data = new TaskObject*[SIZE];
		count = 0;
	}
	// Deconstructor
	~ToDoQueue() {}
	// Insert items into the queue descending in priority order
	void Insert(TaskObject* item) {
		if (isEmpty() == true) {
			// If the queue is empty, add the item
			data[count++] = item;
		} else {
			int i;
			// Loop through all the items in the queue
			for (i = (count - 1); i >= 0; i--) {
				// If the item priority is less that looped item
				if (*item < *data[i]) {
					// Move the looped item to the next index
					data[i + 1] = data[i];
				} else {
					// Break the loop when found its prioritised place
					break;
				}
			}
			// Add the item to its prioritised place in the queue
			data[i + 1] = item;
			count++;
		}
	}
	// Remove an item from the queue
	TaskObject* Remove() {
		count--;
		return data[count];
	}
	// Boolean to check if the queue is empty or not
	bool isEmpty() {
		return count == 0;
	}
};
