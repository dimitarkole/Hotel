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

	friend ostream& operator<<(ostream& out, const Date& date);
	friend istream& operator>>(istream& in, const Time& time);
};
