#pragma once
#pragma warning(disable:4996)

#include "ReservationsService.h"
#include "RoomsService.h"
#include "RoomsController.h"
#include "CloseRoom.h"

class ReservationsController
{
private:
	ReservationsService reservationsService;
	
	void readFromFile();
	void printFreeRoom(const Room* freeRooms, const size_t freeRoomsCount, const Date& date) const;
	const Room* getFreeRoom(const Room* rooms, const size_t roomsCount, const Date& date, size_t& freeRoomsCount) const;
	const Room* getFreeRoom(const Room* rooms, const size_t roomsCount, const Period& period, size_t& freeRoomsCount, const size_t minCountOfBeds) const;
	void printRoomWithMinBedsCount(const Room* freeRooms, const size_t freeRoomsCount) const;
	void removeClosedRooms(const Room* freeRooms, size_t& freeRoomsCount, const CloseRoom* closedRooms, const size_t closedRoomsCount, const Period& period) const;
	void removeClosedRooms(const Room* freeRooms, size_t& freeRoomsCount, const CloseRoom* closedRooms, const size_t closedRoomsCount, const Date& period) const;
	bool isRoomClosed(const size_t roomId, const Date& date, const CloseRoom* closedRooms, const size_t closedRoomsCount) const;
	bool isRoomClosed(const size_t roomId, const Period& date, const CloseRoom* closedRooms, const size_t closedRoomsCount) const;
public:
	ReservationsController();
	
	const Reservation* getReservations() const;
	const size_t getReservationsCount() const;

	void readFromConsole(const CloseRoom* closedRooms, const size_t closedRoomsCount);
	void writeToFile() const;
	void writeToConsole() const;
	void writeToFileReservetedRoomsInPeriod() const;
	void viewFreeRoom(const Room* rooms, const size_t roomsCount, const CloseRoom* closedRooms, const size_t closedRoomsCount) const;
	void searchFreeRoom(const Room* rooms, const size_t roomsCount, const CloseRoom* closedRooms, const size_t closedRoomsCount) const;
	void removeReservation();
};
