#include <iostream>
#include <string>
#include "ToDoQueue.h"
#include "TaskObject.h"
#include "ToDoHashTable.h"

using namespace std;

#define END "END"
#define EXIT "EXIT"
#define MENU "MENU"

int main() {
	cout << "\n--------------------------------------------------------------------" << endl;
	cout << "\n                             To-Do List" << endl;
	cout << "\n--------------------------------------------------------------------" << endl;
	cout << "\n         Input your task and the priority between 1 and 3" << endl;
	cout << "\n                 (1 = Low, 2 = Medium, 3 = High)\n" << endl;
	cout << "\n       Type 'END' to stop inputting and to view your list!" << endl;
	cout << "\n--------------------------------------------------------------------\n" << endl;

	// Boolean values used to break the while loops for user input
	bool userAddingTasks = true;
	bool userRunningApplication = true;
	bool userIsInMenu = true;

	// Initialise the priority queue
	ToDoQueue *toDoList = new ToDoQueue();

	// Loop through until userAddingTasks is set to false
	while (userAddingTasks) {
		string userTaskInput;
		int userPriorityInput;

		cout << "Enter the task: ";
		getline(cin, userTaskInput);

		// If user inputs "END" exit the while loop
		if (userTaskInput == END) {
			userAddingTasks = false;
			break;
		}

		// Get the users input for the task priority, only if they enter 1, 2 or 3
		do {
			cout << "Enter the Priority (1 = Low, 2 = Medium, 3 = High): ";
			cin >> userPriorityInput;
			cout << endl;
			cin.ignore();
			cin.clear();
		} while (userPriorityInput < 1 || userPriorityInput > 3);

		// Insert the inputs into the priority queue
		toDoList->Insert(new TaskObject(userPriorityInput, userTaskInput));
	}

	cout << "\n--------------------------------------------------------------------" << endl;
	cout << "\nYour Prioritised To-Do List:\n" << endl;

	// Initialise the hash table
	ToDoHashTable *table = new ToDoHashTable();

	// Loop through all the items in the priority queue
	while (!toDoList->isEmpty()) {
		// Remove the top item in the priority queue and output it's details
		TaskObject *item = toDoList->Remove();
		cout << "Priority: " << item->priority << "\t Task: " << item->task << endl;
		
		// Insert the item into the hash table
		table->Insert(item);
	}

	// Display the hash table with all the todo items
	cout << "\nYour To-Do List Table:" << endl;
	table->Display();

	// Loop through until userRunningApplication is set to false
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

		// If user inputs "EXIT" exit the while loop and close the application
		if (userChoiceInput == EXIT) {
			userRunningApplication = false;
			break;
		}

		userIsInMenu = true;
		
		// Loop through until userIsInMenu is set to false
		while (userIsInMenu) {
			// If the user enters "1" to Search
			if (userChoiceInput == "1") {
				string userSearchInput;
				TaskObject *objToFind;

				cout << "\n--------------------------------------------------------------------" << endl;
				cout << "                              Search" << endl;
				cout << "               Type 'MENU' to go back to the menu!" << endl;
				cout << "--------------------------------------------------------------------\n" << endl;

				cout << "Search by task name: ";
				getline(cin, userSearchInput);

				// If user inputs "MENU" exit the while loop and return into the menu loop
				if (userSearchInput == MENU) {
					userIsInMenu = false;
					break;
				}

				// Search the hash table for the users inputted task name
				objToFind = table->Search(userSearchInput);
				if (objToFind && objToFind->task == userSearchInput) {
					// If the task name they entered was found, display a message
					cout << "\nFound Task '" << userSearchInput << "'!" << endl;
					cout << "Priority: " << objToFind->priority << endl;
				} else {
					// If the task name they entered could not be found, display a message
					cout << "\nTask '" << userSearchInput << "' could not be found." << endl;
				}
			} 
			// If the user enters "2" to Complete a task
			else if (userChoiceInput == "2") {
				string userTaskNameInput;
				TaskObject *objToComplete;

				cout << "\n--------------------------------------------------------------------" << endl;
				cout << "                        Complete a task" << endl;
				cout << "               Type 'MENU' to go back to the menu!" << endl;
				cout << "--------------------------------------------------------------------\n" << endl;

				cout << "Enter the name of the task you wish to mark as complete: " << endl;
				getline(cin, userTaskNameInput);

				// If user inputs "MENU" exit the while loop and return into the menu loop
				if (userTaskNameInput == MENU) {
					userIsInMenu = false;
					break;
				}

				// Search the hash table for the users inputted task name and remove it
				objToComplete = table->CompleteTask(userTaskNameInput);
				if (objToComplete && objToComplete->task == userTaskNameInput) {
					// If the task name they entered was found, display a message and output the new todo hash table
					cout << "\nTask '" << userTaskNameInput << "' has been completed and removed from your list!" << endl;
					cout << "\n--------------------------------------------------------------------" << endl;
					cout << "\nYour New To-Do List Table:\n" << endl;
					table->Display();
				} else {
					// If the task name they entered could not be found, display a message
					cout << "\nTask '" << userTaskNameInput << "' could not be found." << endl;
				}
			}
		}
	}
	
	return 0;
}