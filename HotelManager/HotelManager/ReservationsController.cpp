#pragma warning(disable:4996)
#include "ReservationsController.h"
#include<iostream>
#include<cmath>
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

	try
	{
		file >> reservationsService;
		file.close();
	}
	catch (const std::exception&)
	{
	}
}

const Reservation* ReservationsController::getReservations() const {
	return reservationsService.getReservations();
}

const size_t ReservationsController::getReservationsCount() const {
	return reservationsService.getReservationsCount();
}

void ReservationsController::readFromConsole(const CloseRoom* closedRooms, const size_t closedRoomsCount) {
	Reservation reservation;
	do {
		cout << "Input reservation data:" << endl;
		cin >> reservation;
		if (!reservationsService.isRoomFree(reservation.getRoomId(), reservation.getPeriod()))
		{
			cout << "This room is reservated in this period!" << endl;
		}
		else if (isRoomClosed(reservation.getRoomId(), reservation.getPeriod(), closedRooms, closedRoomsCount)) {
			cout << "This room is closed in this period!" << endl;
		}
		else {
			break;
		}
	} while (true);
	
	reservationsService.create(reservation);
}

void ReservationsController::writeToFile() const {
	ofstream file(RESERVATION_FILE_NAME, ios::binary);
	if (!file.is_open()) {
		return;
	}

	try
	{
		file << reservationsService;
		file.close();
	}
	catch (const std::exception&)
	{
	}
}

void ReservationsController::writeToConsole() const {
	cout << reservationsService;
}

const Room* ReservationsController::getFreeRoom(const Room* rooms, const size_t roomsCount, const Date& date, size_t& freeRoomsCount) const {
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

const Room* ReservationsController::getFreeRoom(const Room* rooms, const size_t roomsCount, const Period& period, size_t& freeRoomsCount, const size_t minCountOfBeds) const {
	freeRoomsCount = 0;
	Room* freeRooms = new Room[freeRoomsCount];
	for (size_t i = 0; i < roomsCount; i++)
	{
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

void ReservationsController::viewFreeRoom(const Room* rooms, const size_t roomsCount, const CloseRoom* closedRooms, const size_t closedRoomsCount) const{
	size_t freeRoomsCount = 0;
	cout << "Input date:" << endl;
	Date date;//(2022, 5, 4);//, 5, 4);
	cin >> date;
	const Room* freeRooms = getFreeRoom(rooms, roomsCount, date, freeRoomsCount);
	removeClosedRooms(freeRooms, freeRoomsCount, closedRooms, closedRoomsCount, date);
	printFreeRoom(freeRooms, freeRoomsCount, date);
	delete[] freeRooms;
}

void ReservationsController::removeClosedRooms(const Room* freeRooms, size_t& freeRoomsCount, const CloseRoom* closedRooms, const size_t closedRoomsCount, const Date& date) const {
	for (size_t i = 0; i < freeRoomsCount; i++)
	{
		const size_t freeRoomId = freeRooms[i].getId();
		if (isRoomClosed(freeRoomId, date, closedRooms, closedRoomsCount))
		{
			Room* newFreeRooms = new Room[freeRoomsCount - 1];
			for (size_t j = 0; j < freeRoomsCount; j++)
			{
				if(freeRooms[j].getId() == freeRoomId)
				{
					continue;
				}

				newFreeRooms[j] = freeRooms[j];
			}

			delete[] freeRooms;
			freeRooms = newFreeRooms;
			freeRoomsCount--;
		}
	}
}

bool ReservationsController::isRoomClosed(const size_t roomId, const Date& date, const CloseRoom* closedRooms, const size_t closedRoomsCount) const {
	for (size_t i = 0; i < closedRoomsCount; i++)
	{
		if (closedRooms[i].getRoomId() == roomId)
		{
			if (closedRooms[i].getPeriod().getFrom() < date && date < closedRooms[i].getPeriod().getTo())
			{
				return true;
			}
		}
	}

	return true;
}

bool ReservationsController::isRoomClosed(const size_t roomId, const Period& period, const CloseRoom* closedRooms, const size_t closedRoomsCount) const
{
	const Date from = period.getFrom();
	const Date to = period.getTo();
	for (size_t i = 0; i < closedRoomsCount; i++)
	{
		if (closedRooms[i].getRoomId() == roomId)
		{
			if ((closedRooms[i].getPeriod().getFrom() > from && to <= closedRooms[i].getPeriod().getTo())
				|| (from < closedRooms[i].getPeriod().getFrom() && closedRooms[i].getPeriod().getTo() < to))
			{
				return true;
			}

		}
	}

	return false;
}

void ReservationsController::removeClosedRooms(const Room* freeRooms, size_t& freeRoomsCount, const CloseRoom* closedRooms, const size_t closedRoomsCount, const Period& period) const {
	for (size_t i = 0; i < freeRoomsCount; i++)
	{
		size_t freeRoomId = freeRooms[i].getId();
		cout << "freeRoomId = " << freeRoomId << endl;
		if (isRoomClosed(freeRoomId, period, closedRooms, closedRoomsCount))
		{
			cout << "Room is closed " << freeRooms[i];
			Room* newFreeRooms = new Room[freeRoomsCount - 1];
			size_t index = 0;
			for (size_t j = 0; j < freeRoomsCount; j++)
			{
				if (freeRooms[j].getId() == freeRoomId)
				{
					continue;
				}

				newFreeRooms[index] = freeRooms[j];
				index++;
			}

			delete[] freeRooms;
			freeRooms = newFreeRooms;
			freeRoomsCount--;
			i = i - 1 < 0 ? 0 : i - 1;
		}
	}
}

void ReservationsController::searchFreeRoom(const Room* rooms, const size_t roomsCount, const CloseRoom* closedRooms, const size_t closedRoomsCount) const
{
	size_t freeRoomsCount = 0;
	cout << "Input period:" << endl;
	Period period;
	cin >> period;
	cout << "Input min count of beds:" << endl;
	size_t countOfBeds;
	cin >> countOfBeds;
	const Room* freeRooms = getFreeRoom(rooms, roomsCount, period, freeRoomsCount, countOfBeds);
	removeClosedRooms(freeRooms, freeRoomsCount, closedRooms, closedRoomsCount, period);

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

	file << "Reservations count: " << reservatedRoomsCount << endl;
	for (size_t i = 0; i < reservatedRoomsCount; i++)
	{
		// cout << "reservatedRooms[" << i<<"]:" << reservatedRooms[i] << endl;
		reservatedRooms[i].saveToTextFile(file);
		file << endl;
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
