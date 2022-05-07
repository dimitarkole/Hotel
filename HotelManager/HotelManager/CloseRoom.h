#pragma once
#pragma warning(disable:4996)
#include<iostream>
#include "Period.h"

using namespace std;

class CloseRoom
{
private:
	Period period;
	size_t roomId, descriptionLen;
	char *description;

	void free();
	void copyFrom(const CloseRoom& other);
public:
	CloseRoom();
	CloseRoom(const CloseRoom& other);
	~CloseRoom();
	CloseRoom& operator=(const CloseRoom& other);

	void setPeriod(const Period& period);
	void setRoomId(const size_t roomId);
	void setDescription(const char* description);

	const Period& getPeriod() const;
	const size_t  getRoomId() const;
	const char* getDescription() const;
	const size_t getDescriptionLen() const;

	friend ostream& operator<<(ostream& out, const CloseRoom& CloseRoom);
	friend ofstream& operator<<(ofstream& out, const CloseRoom& CloseRoom);
	friend istream& operator>>(istream& in, CloseRoom& CloseRoom);
	friend ifstream& operator>>(ifstream& in, CloseRoom& CloseRoom);
};
