#pragma warning(disable:4996)

#include "Reservation.h"

const size_t MAX_GOST_NAME_LEN = 1024, MAX_DESCRIPTION_LEN = 8 * 1024;

size_t Reservation::maxId = 0;

void Reservation::free() {
	delete[] gostName;
	delete[] description;
}

void Reservation::copyFrom(const Reservation& other) {
	gostName = nullptr;
	description = nullptr;
	this->period = other.period;
	roomId = other.roomId;
	setGostName(other.gostName);
	setDescription(other.description);
	setId(other.id);
}

bool Reservation::isReservationInPeriod(const Period period) const
{
	return period.getFrom() <= this->period.getFrom() && this->period.getTo() <= period.getTo();
}

Reservation::Reservation() {
	this->gostName = nullptr;
	this->description = nullptr;
	this->period = Period();
	this->roomId = 0;
	setGostName("");
	setId(maxId++);
	setDescription("");
}

Reservation::Reservation(size_t roomId, const Period& period, char* gostName, char* description) {
	this->gostName = nullptr;
	this->description = nullptr;
	this->period = period;
	this->roomId = roomId;
	setGostName(gostName);
	setId(maxId++);
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

void Reservation::setPeriod(const Period& period) {
	this->period = period;
}

void Reservation::setRoomId(const size_t roomId) {
	this->roomId = roomId;
}

void Reservation::setId(const size_t id) {
	this->id = id;
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

const Period& Reservation::getPeriod() const {
	return period;
}

const size_t Reservation::getRoomId() const {
	return roomId;
}

const size_t  Reservation::getId() const {
	return id;
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

void Reservation::saveToTextFile(ofstream& out) const {
	out << "id: " << id;
	out << " room id: " << roomId;
	out << " gost name:" << gostName;
	period.saveToFile(out);
	out << " description: ";
	out << description;
}

ostream& operator<<(ostream& out, const Reservation& reservation) {
	out << "id: " << reservation.id;
	out << " room id: " << reservation.roomId;
	out << " gost name:" << reservation.gostName;
	out << reservation.period;
	out << " description: ";
	out << reservation.description;
	return out;
}

ofstream& operator<<(ofstream& out, const Reservation& reservation) {
	out.write((const char*)&reservation.id, sizeof(reservation.id));
	out.write((const char*)&reservation.roomId, sizeof(reservation.roomId));
	out.write((const char*)&reservation.gostNameLen, sizeof(reservation.gostNameLen));
	out.write(reservation.gostName, reservation.gostNameLen);
	out << reservation.period;
	out.write((const char*)&reservation.descriptionLen, sizeof(reservation.descriptionLen));
	out.write(reservation.description, reservation.descriptionLen);
	return out;
}

istream& operator>>(istream& in, Reservation& reservation) {
	cout << "Input roomId:" << endl;
	in >> reservation.roomId;
	char newLine;
	char* gostName = new char[MAX_GOST_NAME_LEN + 1];
	in.get(newLine);
	cout << "Input gost name:" << endl;
	in.getline(gostName, MAX_GOST_NAME_LEN);
	reservation.setGostName(gostName);
	in >> reservation.period;
	in.get(newLine);
	cout << "Input to description:" << endl;
	char* description = new char[MAX_DESCRIPTION_LEN + 1];
	in.getline(description, MAX_DESCRIPTION_LEN);
	reservation.setId(reservation.maxId++);
	reservation.setDescription(description);
	delete[] gostName;
	delete[] description;
	return in;
}

ifstream& operator>>(ifstream& in, Reservation& reservation) {
	in.read((char*)&reservation.id, sizeof(reservation.id));
	reservation.maxId = reservation.maxId < reservation.id ? reservation.id : reservation.maxId;
	in.read((char*)&reservation.roomId, sizeof(reservation.roomId));
	size_t gostNameLen = 0;
	in.read((char*)&gostNameLen, sizeof(gostNameLen));
	char* gostName = new char[gostNameLen + 1];
	in.read((char*)gostName, gostNameLen);
	gostName[gostNameLen] = 0;
	reservation.setGostName(gostName);
	in >> reservation.period;
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
