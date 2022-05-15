#pragma once
#pragma warning(disable:4996)

#include "CloseRoom.h"
#include "Reservation.h"
#include "CloseRoomsService.h"

class CloseRoomsController
{
private:
	CloseRoomsService closeRoomsService;
	void readFromFile();
public:
	CloseRoomsController();

	void readFromConsole(const Reservation* reservations, const size_t reservationsCount);
	void writeToFile() const;
	void writeToConsole() const;
	const CloseRoom* getClosedRooms() const;
	const size_t getClosedRoomsCount() const;
};
