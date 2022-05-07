#pragma once
#pragma warning(disable:4996)
#include<iostream>
#include<fstream>
using namespace std;
class Room
{
private:
	size_t id;
	size_t bedsCount;

	static size_t maxId;
	void setId(const size_t id);
public:
	Room();
	Room(const size_t bedsCount);
	Room(const size_t id, const size_t bedsCount);

	size_t getId() const;
	size_t getBedsCount() const;

	void setBedsCount(const size_t bedsCount);

	friend ostream& operator<<(ostream& out, const Room& room);
	friend ofstream& operator<<(ofstream& out, const Room& room);
	friend istream& operator>>(istream& in, Room& room);
	friend ifstream& operator>>(ifstream& in, Room& room);
};

