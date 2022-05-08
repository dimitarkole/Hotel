#pragma warning(disable:4996)
#include "ReservationsController.h"
#include<iostream>
#include<fstream>

using namespace std;

const char* RESERVATION_FILE_NAME = "Data/reservations.dat";

ReservationsController::ReservationsController()
{
	// readFromFile();
}

void ReservationsController::readFromFile() {
	ifstream file(RESERVATION_FILE_NAME, ios::binary);
	if (!file.is_open()) {
		return;
	}

	file >> reservationsService;
	try
	{
		file.close();
	}
	catch (const std::exception&)
	{
	}
}

void ReservationsController::readFromConsole() {
	cin >> reservationsService;
}

void ReservationsController::writeToFile() const {
	ofstream file(RESERVATION_FILE_NAME, ios::binary);
	if (!file.is_open()) {
		return;
	}

	file << reservationsService;
	try
	{
		file.close();
	}
	catch (const std::exception&)
	{
	}
}

void ReservationsController::writeToConsole() const {
	cout << reservationsService;
}

Room* ReservationsController::getFreeFreeRoom(const Room* rooms, const size_t roomsCount, const Date& date, size_t& freeRoomsCount) const {
	Room* freeRooms = new Room[freeRoomsCount];
	for (size_t i = 0; i < roomsCount; i++)
	{
		// TO DO: is room closed in period???
		if (reservationsService.isRoomFree(rooms[i].getId(), date))
		{
			Room* newFreeRooms = new Room[freeRoomsCount + 1];
			for (size_t j = 0; j < freeRoomsCount; j++)
			{
				newFreeRooms[j] = freeRooms[j];
			}

			newFreeRooms[freeRoomsCount] = rooms[i];
			delete[] freeRooms;
			freeRooms = newFreeRooms;
			freeRoomsCount++;
		}
	}

	return freeRooms;
}

void ReservationsController::viewFreeRoom(const Room* rooms, const size_t roomsCount) const{
	size_t freeRoomsCount = 0;
	cout << "Input date:" << endl;
	Date date;//(2022, 5, 4);//, 5, 4);
	cin >> date;
	Room* freeRooms = getFreeFreeRoom(rooms, roomsCount, date, freeRoomsCount);
	printFreeRoom(freeRooms, freeRoomsCount, date);
	delete[] freeRooms;
}

void ReservationsController::printFreeRoom(const Room* freeRooms, const size_t freeRoomsCount, const Date& date) const{
	cout << "Count of free rooms: " << freeRoomsCount << " for "<< date << endl;
	for (size_t i = 0; i < freeRoomsCount; i++)
	{
		cout << freeRooms[i] << endl;
	}
}
