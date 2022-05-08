#pragma once
#pragma once
#pragma warning(disable:4996)
#include<iostream>
#include "CloseRoom.h"
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
	void create(const CloseRoom& closeRoom);

	friend ostream& operator<<(ostream& out, const CloseRoomsService& closeRoomServices);
	friend ofstream& operator<<(ofstream& out, const CloseRoomsService& closeRoomServices);
	friend istream& operator>>(istream& in, CloseRoomsService& closeRoomServices);
	friend ifstream& operator>>(ifstream& in, CloseRoomsService& closeRoomServices);
};
