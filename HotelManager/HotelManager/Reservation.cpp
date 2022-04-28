#include<iostream>
#include<fstream>
#include<cstring>

#include "Reservation.h"

using namespace std;

const size_t MAX_GOST_NAME_LEN = 1024, MAX_DESCRIPTION_LEN = 8 * 1024;

void Reservation::free() {
	delete[] gostName;
	delete[] description;
}

void Reservation::copyFrom(const Reservation& other) {
	gostName = nullptr;
	description = nullptr;
	from = other.from;
	to = other.from;
	roomId = other.roomId;
	setGostName(other.gostName);
	setDescription(other.description);
}

Reservation::Reservation(size_t roomId, Date from, Date to, char* gostName, char* desctiption) {
	this->gostName = nullptr;
	this->description = nullptr;
	this->from = from;
	this->to = from;
	this->roomId = roomId;
	setGostName(gostName);
	setDescription(description);
}

Reservation::Reservation(const Reservation& other) {
	copyFrom(other);
}

Reservation::~Reservation() {
	free();
}

Reservation& Reservation::operator=(const Reservation& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

void Reservation::setFrom(const Date from) {
	this->from = from;
}

void Reservation::setTo(const Date to) {
	this->to = to;
}

void Reservation::setRoomId(const size_t roomId) {
	this->roomId = roomId;
}

void Reservation::setGostName(const char* gostName) {
	if (this->gostName != gostName)
	{
		delete[] this->gostName;
		gostNameLen = strlen(gostName);
		this->gostName = new char[gostNameLen + 1];
		strcpy(this->gostName, gostName);
		this->gostName[gostNameLen] = 0;
	}
}

void Reservation::setDescription(const char* description) {
	if (this->description != description)
	{
		delete[] this->description;
		descriptionLen = strlen(description);
		this->description = new char[descriptionLen + 1];
		strcpy(this->description, description);
		this->description[descriptionLen] = 0;
	}
}

const Date& Reservation::getFrom() const {
	return from;
}

const Date& Reservation::getTo() const {
	return to;
}

const size_t  Reservation::getRoomId() const {
	return roomId;
}

const char* Reservation::getGostName() const {
	return gostName;
}

const size_t Reservation::getGostNameLen() const {
	return gostNameLen;
}

const char* Reservation::getDescription() const {
	return description;
}

const size_t Reservation::getDescriptionLen() const {
	return descriptionLen;
}

ostream& operator<<(ostream& out, const Reservation& reservation) {
	out << reservation.roomId << " " << reservation.gostName << " ";
	out << reservation.from << " " << reservation.to << " ";
	out << reservation.description;
	return out;
}

ofstream& operator<<(ofstream& out, const Reservation& reservation) {
	out.write((const char*)&reservation.roomId, sizeof(reservation.roomId));
	out.write((const char*)&reservation.gostNameLen, sizeof(reservation.gostNameLen));
	out.write((const char*)reservation.gostName, sizeof(reservation.gostName));
	out.write((const char*)&reservation.from, sizeof(reservation.from));
	out.write((const char*)&reservation.to, sizeof(reservation.to));
	out.write((const char*)&reservation.descriptionLen, sizeof(reservation.descriptionLen));
	out.write((const char*)reservation.description, sizeof(reservation.description));
	return out;
}

istream& operator>>(istream& in, Reservation& reservation) {
	in >> reservation.roomId;
	char* gostName = new char[MAX_GOST_NAME_LEN + 1];
	in.getline(gostName, MAX_GOST_NAME_LEN);
	gostName[MAX_GOST_NAME_LEN] = 0;
	reservation.setGostName(gostName);
	in >> reservation.from;
	in >> reservation.to;
	char* description = new char[MAX_DESCRIPTION_LEN + 1];
	in.getline(description, MAX_DESCRIPTION_LEN);
	description[MAX_DESCRIPTION_LEN] = 0;
	reservation.setGostName(description);
	delete[] gostName;
	delete[] description;
	return in;
}

ifstream& operator>>(ifstream& in, Reservation& reservation) {
	in.read((char*)&reservation.roomId, sizeof(reservation.roomId));
	size_t gostNameLen;
	in.read((char*)&gostNameLen, sizeof(gostNameLen));
	char* gostName = new char[gostNameLen + 1];
	in.read((char*)gostName, gostNameLen);
	gostName[gostNameLen] = 0;
	reservation.setGostName(gostName);
	in.read((char*)&reservation.from, sizeof(reservation.from));
	in.read((char*)&reservation.to, sizeof(reservation.to));
	size_t descriptionLen;
	in.read((char*)&descriptionLen, sizeof(descriptionLen));
	char* description = new char[descriptionLen + 1];
	in.read((char*)description, descriptionLen);
	description[descriptionLen] = 0;
	reservation.setDescription(description);
	delete[] gostName;
	delete[] description;
	return in;
}
