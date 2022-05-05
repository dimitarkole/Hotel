#pragma once
#pragma warning(disable:4996)
#include<iostream>
#include "Room.h"
using namespace std;

class RoomsService
{
private:
	Room* rooms;
	size_t capacity, roomsCount;
	
	void free();
	void resize();
	void copyFrom(const RoomsService& other);
	void addRoom(const Room& room);
public:
	RoomsService();
	RoomsService(const RoomsService& other);
	~RoomsService();

	RoomsService& operator=(const RoomsService& other);
	const Room& operator[](const size_t index)const;
	Room& operator[](const size_t index);

	const Room* getRoom() const;
	const size_t getCapacity() const;
	const size_t getRoomsCount() const;

	friend ostream& operator<<(ostream& out, const RoomsService& roomsService);
	friend ofstream& operator<<(ofstream& out, const RoomsService& roomsService);
	friend istream& operator>>(istream& in, RoomsService& roomsService);
	friend ifstream& operator>>(ifstream& in, RoomsService& roomsService);
};
