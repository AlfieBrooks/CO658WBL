#include <iostream>
#include <string>
#include "ToDoQueue.h"
#include "TaskObject.h"
#include "ToDoHashTable.h"

using namespace std;

int main() {
	cout << "\n--------------------------------------------------------------------" << endl;
	cout << "\n                             To-Do List" << endl;
	cout << "\n--------------------------------------------------------------------" << endl;
	cout << "\n         Input your task and the priority between 1 and 3" << endl;
	cout << "\n                 (1 = Low, 2 = Medium, 3 = High)\n" << endl;
	cout << "\n       Type 'END' to stop inputting and to view your list!" << endl;
	cout << "\n--------------------------------------------------------------------\n" << endl;

	bool userAddingTasks = true;
	bool userRunningApplication = true;
	bool userIsInMenu = true;
	const string END = "END";
	const string EXIT = "EXIT";
	const string MENU = "MENU";

	ToDoQueue *toDoList = new ToDoQueue(20); // Make this a vector

	while (userAddingTasks) {
		string userTaskInput;
		int userPriorityInput;

		cout << "Enter the task: ";
		getline(cin, userTaskInput);

		if (userTaskInput == END) {
			userAddingTasks = false;
			break;
		}

		do {
			cout << "Enter the Priority (1 = Low, 2 = Medium, 3 = High): ";
			cin >> userPriorityInput;
			cout << endl;
			cin.ignore();
			cin.clear();
		} while (userPriorityInput < 0 || userPriorityInput > 3);

		toDoList->Insert(new TaskObject(userPriorityInput, userTaskInput));
	}

	cout << "\n--------------------------------------------------------------------" << endl;
	cout << "\nYour Prioritised To-Do List:\n" << endl;

	// Create the hash table with the size being a prime number for double hashing
	ToDoHashTable *table = new ToDoHashTable(17);

	while (!toDoList->isEmpty()) {
		TaskObject *obj = toDoList->Remove();
		cout << "Priority: " << obj->priority << "\t Task: " << obj->task << endl;
		
		table->Insert(obj);
	}

	cout << "\nYour To-Do List Table:" << endl;
	table->Display();

	while (userRunningApplication) {
		string userChoiceInput;

		cout << "\n--------------------------------------------------------------------" << endl;
		cout << "\n                             To-Do List" << endl;
		cout << "\n--------------------------------------------------------------------" << endl;
		cout << "\n                 Search or mark a task as Complete" << endl;
		cout << "\n                Type 'EXIT' to exit the application!" << endl;
		cout << "\n--------------------------------------------------------------------" << endl;

		cout << "\nWould you like to Search for or Complete a task (enter 1 or 2):" << endl;
		cout << "1 - Search" << endl;
		cout << "2 - Complete a task" << endl;
		cin >> userChoiceInput;
		cin.ignore();
		cin.clear();

		if (userChoiceInput == EXIT) {
			userRunningApplication = false;
			break;
		}

		userIsInMenu = true;
		
		while (userIsInMenu) {
			if (userChoiceInput == "1") {
				string userSearchInput;
				TaskObject *objToFind;

				cout << "\n--------------------------------------------------------------------" << endl;
				cout << "                              Search" << endl;
				cout << "               Type 'MENU' to go back to the menu!" << endl;
				cout << "--------------------------------------------------------------------\n" << endl;

				cout << "Search by task name: ";
				getline(cin, userSearchInput);

				if (userSearchInput == MENU) {
					userIsInMenu = false;
					break;
				}

				objToFind = table->Search(userSearchInput);
				if (objToFind && objToFind->task == userSearchInput) {
					cout << "\nFound Task '" << userSearchInput << "'!" << endl;
					cout << "Priority: " << objToFind->priority << endl;
				}
				else {
					cout << "\nTask '" << userSearchInput << "' could not be found." << endl;
				}
			} else if (userChoiceInput == "2") {
				string userTaskNameInput;
				TaskObject *objToComplete;

				cout << "\n--------------------------------------------------------------------" << endl;
				cout << "                        Complete a task" << endl;
				cout << "               Type 'MENU' to go back to the menu!" << endl;
				cout << "--------------------------------------------------------------------\n" << endl;

				cout << "Enter the name of the task you wish to mark as complete: " << endl;
				getline(cin, userTaskNameInput);

				if (userTaskNameInput == MENU) {
					userIsInMenu = false;
					break;
				}

				objToComplete = table->CompleteTask(userTaskNameInput);
				if (objToComplete && objToComplete->task == userTaskNameInput) {
					cout << "\nTask '" << userTaskNameInput << "' has been completed and removed from your list!" << endl;
					cout << "\n--------------------------------------------------------------------" << endl;
					cout << "\nYour New To-Do List Table:\n" << endl;
					table->Display();
				}
				else {
					cout << "\nTask '" << userTaskNameInput << "' could not be found." << endl;
				}
			}
		}
	}
	
	return 0;
}