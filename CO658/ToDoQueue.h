#pragma once

using namespace std;

template <class T>
class ToDoQueue {
private:
	int count;
	T **data;
	int size;
public:
	ToDoQueue(int size) :size(size) {
		data = new T*[size];
		count = 0;
	}
	~ToDoQueue() {}
	void Insert(T* taskObject) {
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
	T* Remove() {
		count--;
		return data[count];
	}
	bool isEmpty() {
		return count == 0;
	}
};
