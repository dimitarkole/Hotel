#pragma warning(disable:4996)
#include "RoomsController.h"
#include<iostream>
#include<fstream>
using namespace std;

const char* ROOM_FILE_NAME = "Data/rooms.dat";

RoomsController::RoomsController() {
	readFromFile();
}

void RoomsController::readFromFile() {
	ifstream file(ROOM_FILE_NAME, ios::binary);
	if (!file.is_open()) {
		return;
	}

	try
	{
		file >> roomsService;
		file.close();
	}
	catch (const std::exception&)
	{
	}
}

void RoomsController::readFromConsole() {
	Room room;
	cin >> room;
	roomsService.create(room);
}

void RoomsController::writeToFile() const {
	ofstream file(ROOM_FILE_NAME, ios::binary);
	if (!file.is_open()) {
		return;
	}

	try
	{
		file << roomsService;
		file.close();
	}
	catch (const std::exception&)
	{
	}
}

void RoomsController::writeToConsole() const {
	cout << roomsService;
}

const Room* RoomsController::getRooms() const {
	return roomsService.getRoom();
}

const size_t RoomsController::getRoomsCount() const {
	return roomsService.getRoomsCount();
}
