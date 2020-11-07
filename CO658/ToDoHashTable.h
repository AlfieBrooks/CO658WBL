#pragma once

#include <iostream>
#include <string>
#include "TaskObject.h"

using namespace std;

// Define table sizes as prime numbers to avoid infinte loop
#define TABLE_SIZE 17
#define PRIME 19

class ToDoHashTable {
private:
	TaskObject** data;
	int count;
	// Casts the string to the ASCII int value
	int GetASCIIKey(string key) {
		int ASCIItotal = 0;
		for (int i = 0; i < key.length(); i++) {
			ASCIItotal += (int)key[i];
		}
		return ASCIItotal;
	}
	// First hashing function
	int HashFunction(string key) {
		int ASCIIKey = GetASCIIKey(key);
		return ASCIIKey % TABLE_SIZE;
	}
	// Second hashing function
	int DoubleHashFunction(string key) {
		int ASCIIKey = GetASCIIKey(key);
		return PRIME - (ASCIIKey % TABLE_SIZE);
	}
public:
	// Constructor to initalise the hash table with every value as NULL
	ToDoHashTable() {
		data = new TaskObject*[TABLE_SIZE];
		for (int i = 0; i < TABLE_SIZE; i++) {
			data[i] = NULL;
		}
	}
	// Check if the hash table is full
	bool isFull() {
		return count == TABLE_SIZE;
	}
	// Loop through every item in the table that isn't NULL and output it
	void Display() {
		cout << '\n';
		for (int i = 0; i < TABLE_SIZE; i++) {
			if (data[i] != NULL) {
				cout << "Index: " << i << "\tPriority: " << data[i]->priority << "\tTask: " << data[i]->task << endl;
			}
		}
	}
	// Insert a TaskObject item into the hash table
	void Insert(TaskObject* item) {
		if (isFull()) {
			// Don't insert the item if the table is full
			return;
		}

		string key = item->task;
		// Get the first hash for the task key
		int hash = HashFunction(key);

		if (data[hash] != NULL) {
			// If there is a collision, get second hash
			int doubleHash = DoubleHashFunction(key);
			int index = 1;

			while (true) {
				int newHash = (hash + index * doubleHash) % TABLE_SIZE;

				// If there are no collisions, insert the item
				if (data[newHash] != NULL) {
					data[newHash] = item;
					break;
				}
				index++;
			}
		} else {
			// If there are no collisions, insert the item
			data[hash] = item;
		}
		count++;
	}
	// Search for a task name in the hash table
	TaskObject* Search(string key) {
		// Get both hashs to search for
		int hash = HashFunction(key);
		int doubleHash = DoubleHashFunction(key);
		int index = 0;

		// Loop through hash table whilst it has values in
		while (data[(hash + index * doubleHash) % TABLE_SIZE] != NULL) {
			TaskObject *item = data[(hash + index * doubleHash) % TABLE_SIZE];

			if (item->task == key) {
				// If key can be found, return the item
				return item;
			}
			index++;
		}
		// Key cannot be found
		return NULL;
	}
	// Removes an item in the hash table
	TaskObject* CompleteTask(string key) {
		// Get both hashs to search for
		int hash = HashFunction(key);
		int doubleHash = DoubleHashFunction(key);
		int index = 0;

		// Loop through hash table whilst it has values in
		while (data[(hash + index * doubleHash) % TABLE_SIZE] != NULL) {
			TaskObject *item = data[(hash + index * doubleHash) % TABLE_SIZE];

			if (item->task == key) {
				// If key can be found, remove the item and return the item that was removed
				data[(hash + index * doubleHash) % TABLE_SIZE] = NULL;
				return item;
			}
			index++;
		}
		// Key could not be found
		return NULL;
	}
};
