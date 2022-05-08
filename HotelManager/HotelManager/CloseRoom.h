#pragma once
#pragma warning(disable:4996)
#include "Date.h"
class CloseRoom
{
private:
	Date from, to;
	size_t roomId, descriptionLen;
	char *description;

	void free();
	void copyFrom(const CloseRoom& other);
public:
	CloseRoom();
	CloseRoom(size_t roomId, Date from, Date to, char* desctiption);
	CloseRoom(const CloseRoom& other);
	~CloseRoom();
	CloseRoom& operator=(const CloseRoom& other);

	void setFrom(const Date from);
	void setTo(const Date to);
	void setRoomId(const size_t roomId);
	void setDescription(const char* description);

	const Date& getFrom() const;
	const Date& getTo() const;
	const size_t  getRoomId() const;
	const char* getDescription() const;
	const size_t getDescriptionLen() const;

	friend ostream& operator<<(ostream& out, const CloseRoom& CloseRoom);
	friend ofstream& operator<<(ofstream& out, const CloseRoom& CloseRoom);
	friend istream& operator>>(istream& in, CloseRoom& CloseRoom);
	friend ifstream& operator>>(ifstream& in, CloseRoom& CloseRoom);
};

