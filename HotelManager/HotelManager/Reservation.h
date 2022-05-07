#pragma once
#pragma warning(disable:4996)
#include "Date.h"
class Reservation
{
private:
	Date from, to;
	size_t roomId, gostNameLen, descriptionLen;
	char* gostName, *description;
	
	void free();
	void copyFrom(const Reservation& other);
public:
	Reservation();
	Reservation(size_t roomId, Date from, Date to, char* gostName, char* desctiption);
	Reservation(const Reservation& other);
	~Reservation();
	Reservation& operator=(const Reservation& other);

	void setFrom(const Date from);
	void setTo(const Date to);
	void setRoomId(const size_t roomId);
	void setGostName(const char* gostName);
	void setDescription(const char* description);

	bool isReservationInPeriod(const Date& from, const Date& to) const;

	const Date& getFrom() const;
	const Date& getTo() const;
	const size_t  getRoomId() const;
	const char* getGostName() const;
	const size_t getGostNameLen() const;
	const char* getDescription() const;
	const size_t getDescriptionLen() const;

	friend ostream& operator<<(ostream& out, const Reservation& reservation);
	friend ofstream& operator<<(ofstream& out, const Reservation& reservation);
	friend istream& operator>>(istream& in, Reservation& reservation);
	friend ifstream& operator>>(ifstream& in, Reservation& reservation);
};

