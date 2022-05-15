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

void CloseRoomsController::readFromConsole(const Room* rooms, const size_t roomsCount, const Reservation* reservations, const size_t reservationsCount) {
	CloseRoom closeRoom;
	do {
		cin >> closeRoom;
		if (!closeRoomsService.isRoomExsisting(closeRoom.getRoomId(), rooms, roomsCount)) {
			cout << "This room is not exsisting!" << endl;
		}
		if (closeRoomsService.isRoomClosed(closeRoom.getRoomId(), closeRoom.getPeriod()))
		{
			cout << "This room is closed in period!" << endl;
		}
		if (!closeRoomsService.isRoomFree(closeRoom.getRoomId(), closeRoom.getPeriod(), reservations, reservationsCount))
		{
			cout << "This room is reservated in this period!" << endl;
			cout << closeRoomsService.isRoomFree(closeRoom.getRoomId(), closeRoom.getPeriod(), reservations, reservationsCount) << endl;
		}
		else {
			break;
		}
	} while (true);

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