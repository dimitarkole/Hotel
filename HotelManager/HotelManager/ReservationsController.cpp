#pragma warning(disable:4996)
#include "ReservationsController.h"
#include<iostream>
#include<fstream>

using namespace std;

const char* RESERVATION_FILE_NAME = "Data/reservations.dat";

ReservationsController::ReservationsController()
{
	readFromFile();
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

const Room* ReservationsController::getFreeFreeRoom(const Room* rooms, const size_t roomsCount, const Date& date, size_t& freeRoomsCount) const {
	freeRoomsCount = 0;
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

const Room* ReservationsController::getFreeFreeRoom(const Room* rooms, const size_t roomsCount, const Period& period, size_t& freeRoomsCount, const size_t minCountOfBeds) const {
	freeRoomsCount = 0;
	Room* freeRooms = new Room[freeRoomsCount];
	for (size_t i = 0; i < roomsCount; i++)
	{
		// TO DO: is room closed in period???
		if (rooms[i].getBedsCount() >= minCountOfBeds)
		{
			if (reservationsService.isRoomFree(rooms[i].getId(), period))
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
	}

	return freeRooms;
}

void ReservationsController::viewFreeRoom(const Room* rooms, const size_t roomsCount) const{
	size_t freeRoomsCount = 0;
	cout << "Input date:" << endl;
	Date date;//(2022, 5, 4);//, 5, 4);
	cin >> date;
	const Room* freeRooms = getFreeFreeRoom(rooms, roomsCount, date, freeRoomsCount);
	printFreeRoom(freeRooms, freeRoomsCount, date);
	delete[] freeRooms;
}

void ReservationsController::searchFreeRoom(const Room* rooms, const size_t roomsCount) const
{
	size_t freeRoomsCount = 0;
	cout << "Input period:" << endl;
	Period period;
	cin >> period;
	cout << "Input min count of beds:" << endl;
	size_t countOfBeds;
	cin >> countOfBeds;
	const Room* freeRooms = getFreeFreeRoom(rooms, roomsCount, period, freeRoomsCount, countOfBeds);
	
	if (freeRoomsCount == 0) {
		cout << "No free room in period " << period << endl;
	}
	else {
		printRoomWithMinBedsCount(freeRooms, freeRoomsCount);
	}

	delete[] freeRooms;
}

void ReservationsController::printRoomWithMinBedsCount(const Room* freeRooms, const size_t freeRoomsCount) const {
	Room roomWithMinBedsCount = freeRooms[0];
	for (size_t i = 0; i < freeRoomsCount; i++)
	{
		if (freeRooms[i].getBedsCount() < roomWithMinBedsCount.getBedsCount())
		{
			roomWithMinBedsCount = freeRooms[i];
		}
	}

	cout << "Free room is: " << roomWithMinBedsCount<<endl;
}

void ReservationsController::printFreeRoom(const Room* freeRooms, const size_t freeRoomsCount, const Date& date) const{
	cout << "Count of free rooms: " << freeRoomsCount << " for "<< date << endl;
	for (size_t i = 0; i < freeRoomsCount; i++)
	{
		cout << freeRooms[i] << endl;
	}
}

void ReservationsController::removeReservation() {
	size_t reservationId;
	do {
		cout << "Input reservationId:" << endl;
		cin >> reservationId;
	} while (reservationsService.hasReservation(reservationId));
	
	reservationsService.remove(reservationId);
}

void ReservationsController::writeToFileReservetedRoomsInPeriod() const
{
	size_t reservatedRoomsCount = 0;
	Period period;
	cin >> period;
	const Reservation* reservatedRooms = reservationsService.getReservatedRoomsForPeriod(period, reservatedRoomsCount);
	size_t year = period.getFrom().getYear();
	size_t month = period.getFrom().getMonth();
	size_t day = period.getFrom().getDay();
	char fileName[] = "report-YYYY-MM-DD.txt";
	fileName[7] = year / 1000 + '0';
	fileName[8] = (year / 100) % 10 + '0';
	fileName[9] = (year / 10) % 10 + '0';
	fileName[10] = year % 10 + '0';
	fileName[12] = month / 10 + '0';
	fileName[13] = month % 10 + '0';
	fileName[15] = day / 10 + '0';
	fileName[16] = day % 10 + '0';
	ofstream file(fileName, ios::binary);
	if (!file.is_open()) {
		return;
	}

	file.write((const char*)&reservatedRoomsCount, sizeof(reservatedRoomsCount));
	// cout << "reservatedRoomsCount:" << reservatedRoomsCount << endl;
	for (size_t i = 0; i < reservatedRoomsCount; i++)
	{
		// cout << "reservatedRooms[" << i<<"]:" << reservatedRooms[i] << endl;
		file << reservatedRooms[i];
	}

	delete[] reservatedRooms;

	try
	{
		file.close();
	}
	catch (const std::exception&)
	{
	}
}
