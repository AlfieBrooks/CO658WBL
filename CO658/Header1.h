#pragma once

class ToDoList {
private:
	int count;
	int* data;
	int size;
public:
	ToDoList(int size) {
		this->size = size;
		data = new int[size];
		count = 0;
	}
	~ToDoList() {}
	void Insert(int item) {
		if (isEmpty() == true) {
			data[0] = item;
			count++;
		}
		else {
			int i;
			for (i = (count - 1); i >= 0; i--) {
				if (item > data[i]) {
					data[i + 1] = data[i];
				}
				else {
					break;
				}

				data[i + 1] = item;
				count++;
			}
		}
	}
	int Remove() {
		count--;
		return data[count];
	}
	bool isEmpty() {
		return count == 0;
	}
	bool isFull() {
		return size == count;
	}
	int PeakMin() {
		return data[count - 1];
	}
	int Size() {
		return this->size;
	}
};
