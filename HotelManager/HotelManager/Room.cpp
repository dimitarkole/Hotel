#pragma warning(disable:4996)
#include<iostream>
#include<fstream>

#include "Room.h"

using namespace std;

size_t Room::maxId = 0;

Room::Room(): Room(0) {
}

Room::Room(const size_t bedsCount) {
	setBedsCount(bedsCount);
}

Room::Room(const size_t id, const size_t bedsCount) {
	setBedsCount(bedsCount);
}

size_t Room::getId() const {
	return id;
}

size_t Room::getBedsCount() const {
	return bedsCount;
}

void Room::setId(const size_t id) {
	this->id = id;
}

void Room::setBedsCount(const size_t bedsCount) {
	this->bedsCount = bedsCount;
}

ostream& operator<<(ostream& out, const Room& room) {
	out << "roomId: "<<room.getId() << " beds count: " << room.getBedsCount();
	return out;
}

ofstream& operator<<(ofstream& out, const Room& room) {
	size_t roomId = room.getId();
	size_t bedsCount = room.getBedsCount();
	out.write((const char*)&roomId, sizeof(roomId));
	out.write((const char*)&bedsCount, sizeof(bedsCount));
	return out;
}

istream& operator>>(istream& in, Room& room) {
	size_t bedsCount;
	cout << "Input count of bed in room: ";
	in >> bedsCount;
	room.setBedsCount(bedsCount);
	room.setId(room.maxId++);
	return in;
}

ifstream& operator>>(ifstream& in, Room& room) {
	size_t roomId, bedsCount;
	in.read((char*)&roomId, sizeof(roomId));
	in.read((char*)&bedsCount, sizeof(bedsCount));
	room.setBedsCount(bedsCount);
	room.setId(roomId);
	room.maxId = room.maxId < roomId ? roomId : room.maxId + 1;
	return in;
}
