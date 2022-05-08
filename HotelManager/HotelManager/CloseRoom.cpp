#pragma warning(disable:4996)
#include<iostream>
#include<fstream>
#include<cstring>

#include "CloseRoom.h"

using namespace std;

const size_t MAX_GOST_NAME_LEN = 1024, MAX_DESCRIPTION_LEN = 8 * 1024;

void CloseRoom::free() {
	delete[] description;
}

void CloseRoom::copyFrom(const CloseRoom& other) {
	description = nullptr;
	from = other.from;
	to = other.from;
	roomId = other.roomId;
	setDescription(other.description);
}

CloseRoom::CloseRoom() {
	this->description = nullptr;
	this->from = Date();
	this->to = Date();
	this->roomId = 0;
	setDescription("");
}

CloseRoom::CloseRoom(size_t roomId, Date from, Date to, char* description) {
	this->description = nullptr;
	this->from = from;
	this->to = from;
	this->roomId = roomId;
	setDescription(description);
}

CloseRoom::CloseRoom(const CloseRoom& other) {
	copyFrom(other);
}

CloseRoom::~CloseRoom() {
	free();
}

CloseRoom& CloseRoom::operator=(const CloseRoom& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

void CloseRoom::setFrom(const Date from) {
	this->from = from;
}

void CloseRoom::setTo(const Date to) {
	this->to = to;
}

void CloseRoom::setRoomId(const size_t roomId) {
	this->roomId = roomId;
}

void CloseRoom::setDescription(const char* description) {
	if (this->description != description)
	{
		delete[] this->description;
		descriptionLen = strlen(description);
		this->description = new char[descriptionLen + 1];
		strcpy(this->description, description);
		this->description[descriptionLen] = 0;
	}
}

const Date& CloseRoom::getFrom() const {
	return from;
}

const Date& CloseRoom::getTo() const {
	return to;
}

const size_t  CloseRoom::getRoomId() const {
	return roomId;
}

const char* CloseRoom::getDescription() const {
	return description;
}

const size_t CloseRoom::getDescriptionLen() const {
	return descriptionLen;
}

ostream& operator<<(ostream& out, const CloseRoom& closeRoom) {
	out << "room id: " << closeRoom.roomId << " From:";
	out << closeRoom.from << " To:" << closeRoom.to << " Description: ";
	out << closeRoom.description;
	return out;
}

ofstream& operator<<(ofstream& out, const CloseRoom& closeRoom) {
	out.write((const char*)&closeRoom.roomId, sizeof(closeRoom.roomId));
	out << closeRoom.from;
	out << closeRoom.to;
	out.write((const char*)&closeRoom.descriptionLen, sizeof(closeRoom.descriptionLen));
	out.write((const char*)closeRoom.description, sizeof(closeRoom.description));
	return out;
}

istream& operator>>(istream& in, CloseRoom& closeRoom) {
	cout << "Input roomId:" << endl;
	in >> closeRoom.roomId;
	cout << "Input from date:" << endl;
	in >> closeRoom.from;
	cout << "Input to date:" << endl;
	in >> closeRoom.to;
	cout << "Input to description:" << endl;
	char newLine;
	in.get(newLine);
	char* description = new char[MAX_DESCRIPTION_LEN + 1];
	in.getline(description, MAX_DESCRIPTION_LEN);
	description[MAX_DESCRIPTION_LEN] = 0;
	closeRoom.setDescription(description);
	delete[] description;
	return in;
}

ifstream& operator>>(ifstream& in, CloseRoom& closeRoom) {
	in.read((char*)&closeRoom.roomId, sizeof(closeRoom.roomId));
	in >> closeRoom.from;
	in >> closeRoom.to;
	size_t descriptionLen;
	in.read((char*)&descriptionLen, sizeof(descriptionLen));
	char* description = new char[descriptionLen + 1];
	in.read((char*)description, descriptionLen);
	description[descriptionLen] = 0;
	closeRoom.setDescription(description);
	delete[] description;
	return in;
}
