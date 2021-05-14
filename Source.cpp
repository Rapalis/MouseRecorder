#include <iostream>
#include <windows.h>
#include "Player.h"
#include "Recorder.h"
#include <vector>
#include <chrono>
#include <thread>

#define ECS_KEY VK_ESCAPE
using namespace std;
	
static short escKey;
static Recorder recorder;

//void doUntilExit()
//{
//	while (!escKey)
//	{
//		escKey = GetAsyncKeyState(ECS_KEY);
//		std::this_thread::sleep_for(std::chrono::seconds(1));
//	}
//}

int main()
{
	//std::thread exit;
	unsigned char repeatTimes = 0;
	Player player;
	vector<string> fileNames;
	char command;
	string fileName;



	cout << "===============================================" << endl;
	cout << "= [Welcome to simple windows mouse recorder!] =" << endl;
	cout << "= [        Made by Dominykas Rapalis        ] =" << endl;
	cout << "= [                  V 1.3                  ] =" << endl;
	cout << "===============================================" << endl;
	cout << "===============================================" << endl;
	cout << "= [               MENU  COMMANDS            ] =" << endl;
	cout << "===============================================" << endl;
	cout << "= [p-Start playing                          ] =" << endl;
	cout << "= [r-Start recording mouse                  ] =" << endl;
	cout << "= [c-Continue old recording                 ] =" << endl;
	cout << "= [m-Start multiple records                 ] =" << endl;
	cout << "= [ESC-Stop playing/recording               ] =" << endl;
	cout << "= [o-Options                                ] =" << endl;
	cout << "= [e-Exit                                   ] =" << endl;
	cout << "===============================================" << endl;

	do 
	{
		cout << "C:";
		cin >> command;
		switch (command)
		{
		case'm':
			escKey = 0;
			int size;
			cout << "Enter how many files do you want to play:";
			cin >> size;
			fileNames.resize(size);
			for (int i = 0; i < size; i++)
			{
				cout << "Enter " << i+1 << " file's name:";
				cin >> fileName;
				fileNames[i] = fileName;
			}
			ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
			for (int i = 0; i <= repeatTimes; i++)
			{
				cout << "[INFO]: Playing " << i + 1 << " time" << endl;
				for (int i = 0; (i < size) && !escKey; i++)
				{
					if (player.openRecord(fileNames[i]))
					{
						cout << "[INFO]: Playing " << fileNames[i] << "..." << endl;
				
							while (!escKey && player.canPlay())
							{
								player.playLine();
								escKey = GetAsyncKeyState(ECS_KEY);
							}

						player.stop();
						cout << "[INFO]: File" << fileNames[i] << " finished playing" << endl;
					}
					else cout << "[ERROR]: "<< fileNames[i] << " file does not exist in this directory" << endl;

				}
				if (escKey)
					break;
				player.restRecord();
			}
			ShowWindow(GetConsoleWindow(), SW_NORMAL);
			break;
		case 'p':
			escKey = 0;
			cout << "[INFO]: Mouse will start playing when you'll enter file name " << endl;
			cout << "[INFO]: To stop playing press esc button " << endl;
			cout << "Enter file name: ";
			cin.ignore();
			cin >> fileName;
			if (player.openRecord(fileName))
			{
				cout << "[INFO]: Playing " << fileName << "..." << endl;
				ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
				for (int i = 0; i <= repeatTimes; i++)
				{
					cout << "[INFO]: Playing " << i + 1 << " time" << endl;
					//exit = std::thread(doUntilExit);
					while (!escKey && player.canPlay())
					{
						player.playLine();
						escKey = GetAsyncKeyState(ECS_KEY);

					}
					//exit.join();
					if (escKey)
						break;
					player.restRecord();
				}
				
				player.stop();
				cout << "[INFO]: Stopping player" << endl;
				ShowWindow(GetConsoleWindow(), SW_NORMAL);
			}
			else cout << "[ERROR]: This file does not exist in this directory" << endl;						
			break;
		case 'r':
			escKey = 0;
			cout << "[INFO]: Mouse will start recording when you'll enter file name " << endl;
			cout << "[INFO]: To stop recording press esc button " << endl;
			cout << "Enter file name" << endl;
			cin >> fileName;

			cout << "[INFO]: Recording..." << endl;
			ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
			
			//exit = std::thread(doUntilExit);

			while (!escKey)
			{
				recorder.recordLine();
				escKey = GetAsyncKeyState(ECS_KEY);
			}

			//exit.join();

			if (recorder.saveData(fileName))
			{
				recorder.stop();
				cout << "[INFO]: Recording has been saved as " << fileName << endl;
			}
			else cout << "[ERROR]:This file already exist in this directory" << endl;
			ShowWindow(GetConsoleWindow(), SW_NORMAL);
			break;
		case 'o':
			do
			{
				int value;
				double valued;
				cout << "===============================================" << endl;
				cout << "= [               OPTIONS COMMANDS          ] =" << endl;
				cout << "===============================================" << endl;
				cout << "= [s-recording speed(" << player.getSpeed() << ")" << "                     ] =" << endl;
				cout << "= [r-repeat times(" << (int)repeatTimes << ")" << "                        ] =" << endl;
				cout << "= [x-Exit options                           ] =" << endl;
				cout << "===============================================" << endl;
				cout << "C:";
				cin >> command;
				switch (command)
				{
				case 's':
					cout << "Enter speed of the recording:";
					cin >> valued;
					player.setSpeed(valued);
					break;
				case 'r':
					cout << "Enter repeat times of the recording:";
					cin >> value;
					repeatTimes = (unsigned char)value;
					break;
				case 'x':
					break;
				default: cout << "[ERROR]: Invalid command!" << endl;
				}
			} while (command != 'x');
			break;
		case 'c':
			cout << "[INFO]: Mouse will start recording when you'll enter file name " << endl;
			cout << "[INFO]: To stop recording press esc button " << endl;
			cout << "Enter file name" << endl;
			cin >> fileName;
			if (recorder.continueRec(fileName))
			{
				cout << "[INFO]: Recording..." << endl;
				ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
				while (!GetAsyncKeyState(ECS_KEY))
					recorder.recordLine();
				recorder.stop();
				cout << "[INFO]: Recording has been saved as " << fileName << endl;
				ShowWindow(GetConsoleWindow(), SW_NORMAL);
			}
			else cout << "[ERROR]:This file already exist in this directory" << endl;
			break;
		case 'e':
			break;
		default: cout << "[ERROR]: Invalid command!" << endl;
		}
	} while (command != 'e');

	return 0;
}