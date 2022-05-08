#pragma warning(disable:4996)
#include "CloseRoomsController.h"
#include<iostream>
#include<fstream>

using namespace std;

const char* CLOSED_ROOMS_FILE_NAME = "Data/closedRooms.dat";

CloseRoomsController::CloseRoomsController()
{
	readFromFile();
}

void CloseRoomsController::readFromFile() {
	ifstream file(CLOSED_ROOMS_FILE_NAME, ios::binary);
	if (!file.is_open()) {
		return;
	}

	try
	{
		file >> closeRoomsService;
		cout << "Here";
		file.close();
	}
	catch (const std::exception&)
	{
	}
}

void CloseRoomsController::readFromConsole() {
	cin >> closeRoomsService;
}

void CloseRoomsController::writeToFile() const {
	ofstream file(CLOSED_ROOMS_FILE_NAME, ios::binary);
	if (!file.is_open()) {
		return;
	}

	try
	{
		file << closeRoomsService;
		file.close();
	}
	catch (const std::exception&)
	{
	}
}

void CloseRoomsController::writeToConsole() const {
	cout << closeRoomsService;
}
