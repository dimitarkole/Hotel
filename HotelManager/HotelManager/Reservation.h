#pragma once
#pragma warning(disable:4996)
#include<iostream>
#include "Period.h"
using namespace std;
class Reservation
{
private:
	Period period;
	size_t id, roomId, gostNameLen, descriptionLen;
	char* gostName, *description;

	static size_t maxId;
	void free();
	void copyFrom(const Reservation& other);
	void setId(const size_t id);
public:
	Reservation();
	Reservation(size_t roomId, const Period& period, char* gostName, char* desctiption);
	Reservation(const Reservation& other);
	~Reservation();
	Reservation& operator=(const Reservation& other);

	void setPeriod(const Period& period);
	void setRoomId(const size_t roomId);
	void setGostName(const char* gostName);
	void setDescription(const char* description);

	bool isReservationInPeriod(const Period period) const;

	const Period& getPeriod() const;
	const size_t  getId() const;
	const size_t  getRoomId() const;
	const char* getGostName() const;
	const size_t getGostNameLen() const;
	const char* getDescription() const;
	const size_t getDescriptionLen() const;
	void saveToTextFile(ofstream& out) const;

	friend ostream& operator<<(ostream& out, const Reservation& reservation);
	friend ofstream& operator<<(ofstream& out, const Reservation& reservation);
	friend istream& operator>>(istream& in, Reservation& reservation);
	friend ifstream& operator>>(ifstream& in, Reservation& reservation);
};

