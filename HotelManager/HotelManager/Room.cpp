#pragma warning(disable:4996)
#include<iostream>
#include<fstream>
#include "Room.h"
using namespace std;
Room::Room(): Room(0,0) {
}

Room::Room(const size_t id, const size_t bedsCount) {
	setId(id);
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
	out << room.getId() << " " << room.getBedsCount();
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
	size_t roomId, bedsCount;
	in >> roomId >> bedsCount;
	room.setBedsCount(bedsCount);
	room.setId(roomId);
	return in;
}

ifstream& operator>>(ifstream& in, Room& room) {
	size_t roomId, bedsCount;
	in.read((char*)&roomId, sizeof(roomId));
	in.read((char*)&bedsCount, sizeof(bedsCount));
	room.setBedsCount(bedsCount);
	room.setId(roomId);
	return in;
}