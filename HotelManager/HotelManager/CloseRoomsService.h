#pragma once
#pragma warning(disable:4996)
#include<iostream>
#include "CloseRoom.h"
#include "Date.h"
#include "Reservation.h"
#include "CloseRoomsService.h"

using namespace std;
class CloseRoomsService
{
private:
	CloseRoom *closeRooms;
	size_t capacity, closeRoomsCount;
	void free();
	void resize();
	void copyFrom(const CloseRoomsService& other);
public:
	CloseRoomsService();
	CloseRoomsService(const CloseRoomsService& other);
	~CloseRoomsService();
	CloseRoomsService& operator=(const CloseRoomsService& other);
	const CloseRoom& operator[](const size_t index)const;
	CloseRoom& operator[](const size_t index);

	const CloseRoom* getCloseRooms() const;
	const size_t getCapacity() const;
	const size_t getCloseRoomsCount() const;

	bool isRoomClosed(size_t roomId, const Date& date) const;
	bool isRoomClosed(size_t roomId, const Period& period) const;
	void create(const CloseRoom& closeRoom);

	bool isRoomFree(const size_t roomId, const Period& period, const Reservation* reservations, const size_t reservationsCount) const;
	const Reservation& getReservationInPeriod(const size_t roomId, const Period& period, const Reservation* reservations, const size_t reservationsCount) const;

	friend ostream& operator<<(ostream& out, const CloseRoomsService& closeRoomServices);
	friend ofstream& operator<<(ofstream& out, const CloseRoomsService& closeRoomServices);
	//friend istream& operator>>(istream& in, CloseRoomsService& closeRoomServices);
	friend ifstream& operator>>(ifstream& in, CloseRoomsService& closeRoomServices);
};
