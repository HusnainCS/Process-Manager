#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

// Function to list all processes
void ListProcesses() {
    cout << "Listing all processes...\n" << endl;
    system("tasklist");
}

// Function to terminate a process by ID
void TerminateProcessByID(const string& processID) {
    string command = "taskkill /PID " + processID + " /F";
    int result = system(command.c_str());

    if (result == 0) {
        cout << "Process with ID " << processID << " terminated successfully." << endl;
    } else {
        cout << "Failed to terminate process with ID " << processID << "." << endl;
    }
}

int main() {
    int choice;
    string processID;

    do {
        cout << "\n==== Process Manager ====" << endl;
        cout << "1. List all processes" << endl;
        cout << "2. Terminate a process by ID" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            ListProcesses();
            break;
        case 2:
            cout << "Enter Process ID to terminate: ";
            cin >> processID;
            TerminateProcessByID(processID);
            break;
        case 3:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
