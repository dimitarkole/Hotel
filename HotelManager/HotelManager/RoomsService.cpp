#pragma warning(disable:4996)
#include "RoomsService.h"

#include<fstream>
#include<iostream>
using namespace std;

const size_t MIN_CAPACITY = 8;

void RoomsService::free() {
	delete[] rooms;
}

void RoomsService::copyFrom(const RoomsService& other) {
	capacity = other.capacity;
	roomsCount = 0;
	rooms = new Room[capacity];
	for (size_t i = 0; i < other.roomsCount; i++)
	{
		addRoom(other.rooms[i]);
	}
}

void RoomsService::resize() {
	size_t newCapacity = 3*capacity / 4 <= roomsCount ? capacity * 2 : capacity / 2;
	if (newCapacity >= MIN_CAPACITY)
	{
		Room* newRooms = new Room[newCapacity];
		for (size_t i = 0; i < roomsCount; i++)
		{
			newRooms[i] = rooms[i];
		}

		delete[] rooms;
		rooms = newRooms;
		capacity = newCapacity;
	}
}

RoomsService::RoomsService() {
	capacity = MIN_CAPACITY;
	roomsCount = 0;
	rooms = new Room[capacity];
}

RoomsService::RoomsService(const RoomsService& other) {
	copyFrom(other);
}

RoomsService::~RoomsService() {
	free();
}

RoomsService& RoomsService::operator=(const RoomsService& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

const Room& RoomsService::operator[](const size_t index)const {
	if (index >= roomsCount)
	{
		throw "Invalid index";
	}

	return rooms[index];
}

Room& RoomsService::operator[](const size_t index) {
	if (index >= roomsCount)
	{
		throw "Invalid index";
	}

	return rooms[index];
}

const Room* RoomsService::getRoom() const {
	return rooms;
}

const size_t RoomsService::getCapacity() const {
	return capacity;
}

const size_t RoomsService::getRoomsCount() const {
	return roomsCount;
}
	
void RoomsService::addRoom(const Room& room) {
	resize();
	rooms[roomsCount] = room;
	roomsCount++;
	//cout << "This element is added successful!" << endl;
}

ostream& operator<<(ostream& out, const RoomsService& roomsService) {
	out << "Rooms count: " << roomsService.getRoomsCount() << endl;
	for (size_t i = 0; i < roomsService.roomsCount; i++)
	{
		out << roomsService[i] << endl;
	}

	return out;
}

ofstream& operator<<(ofstream& out, const RoomsService& roomsService) {
	size_t roomsCount = roomsService.roomsCount;
	out.write((const char*)&roomsCount, sizeof(roomsCount));
	for (size_t i = 0; i < roomsService.roomsCount; i++)
	{
		Room room = roomsService[i];
		size_t roomId = room.getId();
		size_t bedsCount = room.getBedsCount();
		out.write((const char*)&roomId, sizeof(roomId));
		out.write((const char*)&bedsCount, sizeof(bedsCount));
	}

	return out;
}

istream& operator>>(istream& in, RoomsService& roomsService) {
	size_t roomsCount;
	cout << "Input rooms count"<< endl;
	in >> roomsCount;
	for (size_t i = 0; i < roomsCount; i++)
	{
		cout << "Input count of beds of room "<< i + 1 << endl;
		Room room;
		in >> room;
		roomsService.addRoom(room);
	}

	return in;
}

ifstream& operator>>(ifstream& in, RoomsService& roomsService) {
	size_t roomsCount;
	in.read((char*)&roomsCount, sizeof(roomsCount));
	for (size_t i = 0; i < roomsCount; i++)
	{
		Room room;
		in >> room;
		roomsService.addRoom(room);
	}

	return in;
}
