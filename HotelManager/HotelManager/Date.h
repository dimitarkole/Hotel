#pragma warning(disable:4996)
#pragma once
#include "Time.h"

class Date
{
	size_t year;
	char* monthStr;
	size_t month;
	size_t day;
	Time time;
public:
	Date(const size_t year = 0, const size_t month = 0, const size_t day = 0,
		const size_t hours = 0, const size_t mins = 0, const size_t secs = 0);
	
	void setYear(const size_t year);
	void setMonth(const size_t month);
	void setDay(const size_t day);
	void setTime(const Time& time);

	size_t getYear() const;
	size_t getMonth() const;
	size_t getDay() const;
	const Time& getTime() const;

	bool operator==(const Date& other) const;
	bool operator!=(const Date& other) const;
	bool operator>=(const Date& other) const;
	bool operator<=(const Date& other) const;

	friend ostream& operator<<(ostream& out, const Date& date); // for console
	friend istream& operator>>(istream& in, Date& time); // for console
	friend ofstream& operator<<(ofstream& out, const Date& date); // for file
	friend ifstream& operator>>(ifstream& in, Date& time); // for file
};
