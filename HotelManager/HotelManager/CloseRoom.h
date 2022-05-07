#pragma once
#pragma warning(disable:4996)
#include "Period.h"

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

	Period& getPeriod();
	const size_t  getRoomId() const;
	const char* getDescription() const;
	const size_t getDescriptionLen() const;

	friend ostream& operator<<(ostream& out, const CloseRoom& CloseRoom);
	friend ofstream& operator<<(ofstream& out, const CloseRoom& CloseRoom);
	friend istream& operator>>(istream& in, CloseRoom& CloseRoom);
	friend ifstream& operator>>(ifstream& in, CloseRoom& CloseRoom);
};

