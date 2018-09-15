// SC2HACK.cpp : Defines the entry point for the console application.

//Windows header file for Windows API calls
#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	//Finds a window
	HWND SC2_Window = FindWindow(0, ("Starcraft II"));

	//Needed to open the process
	HANDLE hProcess;

	//Stores Process ID
	DWORD pid;

	//Current amount of minerals
	int minerals;

	//Minerals to be added
	int moreMinerals = 2000;

	//Check if Starcraft II is open
	//If it returns a 0, throw an error
	if (!SC2_Window) {
		//Output
		cout << "ERROR001 <Cannot Find Starcraft II\n\n";

	//If the window was found, get the process ID
	} else {

		//Finds the process ID
		GetWindowThreadProcessId(SC2_Window, &pid);

		cout << "Found Starcraft II Process: " << pid << "\n\n";

		//Sets up process handler, opens process to read/write memory
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

		//If this fails, we need to know
		if (!hProcess) {

			cout << "ERROR002 <Cannot Open Process\n\n";

		} else {

			cout << "Process Opened!\n\n";

			//Want to see if the read works or doesn't work
			//Put our value it into our minerals variable
			if (!ReadProcessMemory(hProcess, (void *)0x026A9448, (void *)&minerals, sizeof(minerals), NULL)) {

				cout << "ERROR003 <Failed to Read memory\n\n";

			} else {
				
				cout << "Value Found: " << minerals << "\n\n";
				//Write process memory to overwrite the value in memory
				if (!WriteProcessMemory(hProcess, (void *)0x026A9448, &moreMinerals, (DWORD)sizeof(moreMinerals), NULL)) {

					cout << "ERROR004 <Failed to Write to Memory>\n\n";

				} else {

					cout << "Memory Written!\n\n";

					ReadProcessMemory(hProcess, (void *)0x026A9448, (void *)&minerals, sizeof(minerals), NULL);

					cout << "New Value: " << minerals << "\n\n";
				}

			}

		}

	}

	CloseHandle(hProcess);
	cout << "Closed Process!\n\n";
	cin.get();
	return 0;
}