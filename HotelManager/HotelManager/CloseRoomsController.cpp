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
		file.close();
	}
	catch (const std::exception&)
	{
	}
}

void CloseRoomsController::readFromConsole() {
	CloseRoom closeRoom;
	do {
		cin >> closeRoom;
	} while (!closeRoomsService.isRoomClosed(closeRoom.getRoomId(), closeRoom.getPeriod()));

	closeRoomsService.create(closeRoom);
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

const CloseRoom* CloseRoomsController::getClosedRooms() const {
	return closeRoomsService.getCloseRooms();
}

const size_t CloseRoomsController::getClosedRoomsCount() const {
	return closeRoomsService.getCloseRoomsCount();
}