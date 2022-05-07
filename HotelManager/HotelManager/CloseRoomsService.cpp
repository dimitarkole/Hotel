#pragma warning(disable:4996)
#include "CloseRoomsService.h"
#include "Period.h"

#include<fstream>
#include<iostream>
using namespace std;
const size_t MIN_CAPACITY = 8;
const size_t MAX_GOST_NAME_LEN = 1024, MAX_DESCRIPTION_LEN = 8 * 1024;

void CloseRoomsService::free() {
	delete[] closeRooms;
}

void CloseRoomsService::copyFrom(const CloseRoomsService& other) {
	capacity = other.capacity;
	closeRoomsCount = 0;
	closeRooms = new CloseRoom[capacity];
	for (size_t i = 0; i < other.capacity; i++)
	{
		create(other.closeRooms[i]);
	}
}

void CloseRoomsService::resize() {
	size_t newCapacity = 3 * capacity / 4 <= closeRoomsCount ? capacity * 2 : capacity / 2;
	if (newCapacity >= MIN_CAPACITY)
	{
		CloseRoom* newCloseRooms = new CloseRoom[newCapacity];
		for (size_t i = 0; i < closeRoomsCount; i++)
		{
			newCloseRooms[i] = closeRooms[i];
		}

		delete[] closeRooms;
		closeRooms = newCloseRooms;
		capacity = newCapacity;
	}
}

CloseRoomsService::CloseRoomsService() {
	capacity = MIN_CAPACITY;
	closeRoomsCount = 0;
	closeRooms = new CloseRoom[capacity];
}

CloseRoomsService::CloseRoomsService(const CloseRoomsService& other) {
	copyFrom(other);
}

CloseRoomsService::~CloseRoomsService() {
	free();
}

CloseRoomsService& CloseRoomsService::operator=(const CloseRoomsService& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

const CloseRoom& CloseRoomsService::operator[](const size_t index)const {
	if (index >= closeRoomsCount)
	{
		throw "Invalid index";
	}

	return closeRooms[index];
}

CloseRoom& CloseRoomsService::operator[](const size_t index) {
	if (index >= closeRoomsCount)
	{
		throw "Invalid index";
	}

	return closeRooms[index];
}

bool CloseRoomsService::isRoomClosed(size_t roomId, const Date& date) const {
	for (size_t i = 0; i < closeRoomsCount; i++)
	{
		if (closeRooms[i].getRoomId() == roomId)
		{
			if (closeRooms[i].getPeriod().getFrom() < date && date < closeRooms[i].getPeriod().getTo())
			{
				return false;
			}
		}
	}

	return true;
}

void CloseRoomsService::create(const CloseRoom& reservation) {
	closeRooms[closeRoomsCount] = reservation;
	closeRoomsCount++;
	resize();
}

const CloseRoom* CloseRoomsService::getCloseRooms() const {
	return closeRooms;
}

const size_t CloseRoomsService::getCapacity() const {
	return capacity;
}

const size_t CloseRoomsService::getCloseRoomsCount() const {
	return closeRoomsCount;
}

ostream& operator<<(ostream& out, const CloseRoomsService& closeRoomsService) {
	size_t closeRoomsCount = closeRoomsService.getCloseRoomsCount();
	out << "CloseRooms count: " << closeRoomsCount << endl;
	for (size_t i = 0; i < closeRoomsCount; i++)
	{
		out << closeRoomsService[i] << endl;
	}

	return out;
}

ofstream& operator<<(ofstream& out, const CloseRoomsService& closeRoomsService) {
	size_t closeRoomsCount = closeRoomsService.closeRoomsCount;
	out.write((const char*)&closeRoomsCount, sizeof(closeRoomsCount));
	for (size_t i = 0; i < closeRoomsCount; i++)
	{
		out << closeRoomsService[i] << endl;
	}

	return out;
}

istream& operator>>(istream& in, CloseRoomsService& closeRoomsService) {
	// size_t closeRoomsCount;
	// cout << "Input closeRooms count:" << endl;
	// in >> closeRoomsCount;
	// for (size_t i = 0; i < closeRoomsCount; i++)
	// {
	CloseRoom closeRoom;
	in >> closeRoom;
	closeRoomsService.create(closeRoom);
	// }
	return in;
}

ifstream& operator>>(ifstream& in, CloseRoomsService& closeRoomsService) {
	size_t closeRoomsCount;
	in.read((char*)&closeRoomsCount, sizeof(closeRoomsCount));
	for (size_t i = 0; i < closeRoomsCount; i++)
	{
		CloseRoom closeRoom;
		in >> closeRoom;
		closeRoomsService.create(closeRoom);
	}

	return in;
}
