#pragma warning(disable:4996)
#include "ReservationsService.h"

#include<fstream>
#include<iostream>
using namespace std;
const size_t MIN_CAPACITY = 8;
const size_t MAX_GOST_NAME_LEN = 1024, MAX_DESCRIPTION_LEN = 8 * 1024;

void ReservationsService::free() {
	delete[] reservations;
}

void ReservationsService::copyFrom(const ReservationsService& other) {
	capacity = other.capacity;
	reservationsCount = 0;
	reservations = new Reservation[capacity];
	for (size_t i = 0; i < other.capacity; i++)
	{
		addReservation(other.reservations[i]);
	}
}

void ReservationsService::resize() {
	size_t newCapacity = 3 * capacity / 4 <= reservationsCount ? capacity * 2 : capacity / 2;
	if (newCapacity >= MIN_CAPACITY)
	{
		Reservation* newReservations = new Reservation[newCapacity];
		for (size_t i = 0; i < reservationsCount; i++)
		{
			newReservations[i] = reservations[i];
		}

		delete[] reservations;
		reservations = newReservations;
		capacity = newCapacity;
	}
}

ReservationsService::ReservationsService() {
	capacity = MIN_CAPACITY;
	reservationsCount = 0;
	reservations = new Reservation[capacity];
}

ReservationsService::ReservationsService(const ReservationsService& other) {
	copyFrom(other);
}

ReservationsService::~ReservationsService() {
	free();
}

ReservationsService& ReservationsService::operator=(const ReservationsService& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

const Reservation& ReservationsService::operator[](const size_t index)const {
	if (index >= reservationsCount)
	{
		throw "Invalid index";
	}

	return reservations[index];
}

Reservation& ReservationsService::operator[](const size_t index) {
	if (index >= reservationsCount)
	{
		throw "Invalid index";
	}

	return reservations[index];
}

bool ReservationsService::isRoomFree(size_t roomId, const Date& date) const {
	for (size_t i = 0; i < reservationsCount; i++)
	{
		if (reservations[i].getRoomId() == roomId)
		{
			if (reservations[i].getFrom() <= date && date <= reservations[i].getTo())
			{
				return false;
			}
		}
	}

	return true;
}

void ReservationsService::addReservation(const Reservation& reservation) {
	reservations[reservationsCount] = reservation;
	reservationsCount++;
	resize();
}

const Reservation* ReservationsService::getReservations() const {
	return reservations;
}

const size_t ReservationsService::getCapacity() const {
	return capacity;
}

const size_t ReservationsService::getReservationsCount() const {
	return reservationsCount;
}

ostream& operator<<(ostream& out, const ReservationsService& reservationsService) {
	size_t reservationsCount = reservationsService.getReservationsCount();
	out<< "Reservations count: " << reservationsCount << endl;
	for (size_t i = 0; i < reservationsCount; i++)
	{
		out << reservationsService[i]<<endl;
	}

	return out;
}

ofstream& operator<<(ofstream& out, const ReservationsService& reservationsService) {
	size_t reservationsCount = reservationsService.reservationsCount;
	out.write((const char*)&reservationsCount, sizeof(reservationsCount));
	for (size_t i = 0; i < reservationsCount; i++)
	{
		out << reservationsService[i] << endl;
	}

	return out;
}

istream& operator>>(istream& in, ReservationsService& reservationsService) {
	// size_t reservationsCount;
	// cout << "Input reservations count:" << endl;
	// in >> reservationsCount;
	// for (size_t i = 0; i < reservationsCount; i++)
	// {
		cout << "Input roomId:" << endl;
		size_t roomId;
		in >> roomId;
		char* gostName = new char[MAX_GOST_NAME_LEN + 1];
		cout << "Input gost name:" << endl;
		char newLine;
		in.get(newLine);
		in.getline(gostName, MAX_GOST_NAME_LEN);
		gostName[MAX_GOST_NAME_LEN] = 0;
		Date from, to;
		cout << "Input from date:" << endl;
		in >> from;
		cout << "Input to date:" << endl;
		in >> to;
		char* description = new char[MAX_DESCRIPTION_LEN + 1];
		cout << "Input to description:" << endl;
		in.get(newLine);
		in.getline(description, MAX_DESCRIPTION_LEN);
		description[MAX_DESCRIPTION_LEN] = 0;
		Reservation reservation(roomId, from, to, gostName, description);
		reservationsService.addReservation(reservation);
		delete[] gostName;
		delete[] description;
	// }
	return in;
}

ifstream& operator>>(ifstream& in, ReservationsService& reservationsService) {
	size_t reservationsCount;
	in.read((char*)&reservationsCount, sizeof(reservationsCount));
	for (size_t i = 0; i < reservationsCount; i++)
	{
		Reservation reservation;
		in >> reservation;
		reservationsService.addReservation(reservation);
	}

	return in;
}
