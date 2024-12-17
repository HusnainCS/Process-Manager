#include <windows.h> // Provides declarations for Windows API functions 
#include <tlhelp32.h> // Provides functions for taking snapshots of system processes
#include <psapi.h> // Provides Fuction to query process information (the series of steps a database management system (DBMS) takes to execute a query)
#include <iostream>

using namespace std;

// Function to list all running processes
void listProcesses() {
    HANDLE hSnapshot;
    PROCESSENTRY32 pe32;

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        cout << "Failed to take a snapshot of processes!" << endl;
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hSnapshot, &pe32)) {
        cout << "Failed to retrieve process information!" << endl;
        CloseHandle(hSnapshot);
        return;
    }

    cout << "------------------------------------------------------" << endl;
    cout << "PID\t\tProcess Name" << endl;
    cout << "------------------------------------------------------" << endl;

    do {
        cout << pe32.th32ProcessID << "\t\t" << pe32.szExeFile << endl;
    } while (Process32Next(hSnapshot, &pe32));

    CloseHandle(hSnapshot);
}

// Function to terminate a process by its PID
void terminateProcess(DWORD processID) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, processID);

    if (hProcess == NULL) {
        cout << "Failed to open process with PID " << processID << ". Invalid PID or insufficient permissions." << endl;
        return;
    }

    if (TerminateProcess(hProcess, 0)) {
        cout << "Process with PID " << processID << " terminated successfully!" << endl;
    } else {
        cout << "Failed to terminate process with PID " << processID << "." << endl;
    }

    CloseHandle(hProcess);
}

int main() {
    int choice;
    DWORD pid;

    while (true) {
        cout << "\n=============== Process Manager ===============" << endl;
        cout << "1. List all running processes" << endl;
        cout << "2. Terminate a process by PID" << endl;
        cout << "3. Exit" << endl;
        cout << "===============================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                listProcesses();
                break;
            case 2:
                cout << "Enter the Process ID (PID) to terminate: ";
                cin >> pid;
                terminateProcess(pid);
                break;
            case 3:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
