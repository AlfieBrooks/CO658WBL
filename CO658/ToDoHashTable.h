#pragma once

#include <iostream>
#include <string>

using namespace std;

template <class T>
class ToDoHashTable {
private:
	T** data;
	int size;
	int HashFunction(string key) {
		int ASCIItot = 0;
		for (int i = 0; i < key.length(); i++) {
			ASCIItot += (int)key[i];
		}
		return ASCIItot % size;
	}
public:
	ToDoHashTable(int size) :size(size) {
		data = new T*[size];
		for (int i = 0; i < size; i++)
			data[i] = NULL;
	}
	void Display() {
		cout << '\n';
		for (int i = 0; i < size; i++) {
			if (data[i] != NULL) {
				cout << "Index: " << i << "\tPriority: " << data[i]->priority << "\tTask: " << data[i]->task << endl;
			}
		}
	}
	void Insert(T* item) {
		string key = item->task;
		int hash = HashFunction(key);
		while (data[hash] != NULL) {
			++hash;
			hash %= size;
		}
		data[hash] = item;
	}
	T* Search(string key) {
		int hash = HashFunction(key);
		while (data[hash] != NULL) {
			if (data[hash]->task == key) {
				return data[hash];
			}
			hash++;
			hash = hash % size;
		}
		return NULL;
	}
	T* CompleteTask(string key) {
		int hash = HashFunction(key);
		while (data[hash] != NULL) {
			if (data[hash]->task == key) {
				T *taskToDelete = data[hash];
				data[hash] = NULL;
				return taskToDelete;
			}
			hash++;
			hash = hash % size;
		}
		return NULL;
	}
};
