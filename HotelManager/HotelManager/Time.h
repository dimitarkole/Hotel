#pragma once
#pragma warning(disable:4996)
#include <fstream>
using namespace std;

class Time
{
	size_t hours;
	size_t mins;
	// size_t secs;
	size_t convertToMins() const;
public:
	Time(size_t hours = 0, size_t mins = 0);//, size_t secs = 0);

	void setHours(size_t);
	void setMins(size_t);
	// void setSecs(size_t);

	size_t getHours();
	size_t getMins();
	// size_t getSecs();

	bool operator==(const Time& other) const;
	bool operator!=(const Time& other) const;
	bool operator>=(const Time& other) const;
	bool operator<=(const Time& other) const;

	friend ostream& operator<<(ostream& out, const Time& time);
	friend ofstream& operator<<(ofstream& out, const Time& time);
	friend istream& operator>>(istream& in, Time& time);
	friend ifstream& operator>>(ifstream& in, Time& time);
};
