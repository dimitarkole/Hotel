#pragma once
#pragma warning(disable:4996)

#include "ReservationsService.h"
#include "RoomsService.h"
#include "RoomsController.h"

class ReservationsController
{
private:
	ReservationsService reservationsService;
	
	void readFromFile();
	void printFreeRoom(const Room* freeRooms, const size_t freeRoomsCount, const Date& date) const;
	Room* getFreeFreeRoom(const Room* rooms, const size_t roomsCount, const Date& date, size_t& freeRoomsCount) const;
public:
	ReservationsController();
	
	void readFromConsole();
	void writeToFile() const;
	void writeToConsole() const;
	void viewFreeRoom(const Room* rooms, const size_t roomsCount) const;
};
