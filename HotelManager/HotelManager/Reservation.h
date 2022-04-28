#pragma once
#include "Date.h"
class Reservation
{
private:
	Date from, to;
	size_t roomId, gostNameLen, descriptonLen;
	char* gostName, *descripton;
	
	void free();
	void copyFrom(const Reservation& other);
public:	
	Reservation(Date from, Date to, char* gostName, char* desctiption);
	Reservation(const Reservation& other);
	~Reservation();
	Reservation& operator=(const Reservation& other);

	void setFrom(const Date from);
	void setTo(const Date to);
	void setRoomId(const size_t roomId);
	void setGostName(const char* gostName);
	void setDescripton(const char* descripton);

	const Date& getFrom() const;
	const Date& getTo() const;
	const size_t  getRoomId() const;
	const char* getGostName() const;
	const size_t getGostNameLen() const;
	const char* getDescripton() const;
	const size_t getDescriptonLen() const;

	friend ostream& operator<<(ostream& out, const Reservation& reservation);
	friend ofstream& operator<<(ofstream& out, const Reservation& reservation);
	friend istream& operator>>(istream& in, Reservation& reservation);
	friend ifstream& operator>>(ifstream& in, Reservation& reservation);
};

