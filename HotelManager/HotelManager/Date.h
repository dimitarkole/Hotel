#pragma warning(disable:4996)
#pragma once
#include "Time.h"

class Date
{
	size_t day;
	size_t month;
	size_t year;

	size_t MAX_DAYS[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	mutable int dayOfWeek;
	mutable bool isModified = true;

	bool isLeapYear() const;
	void validateDateByChangedCalendars();

	//Time time;
public:
	Date(const size_t year = 0, const size_t month = 0, const size_t day = 0);
		//const size_t hours = 0, const size_t mins = 0, const size_t secs = 0);
	bool areEqual(const Date& other) const;
	void setYear(const size_t year);
	void setMonth(const size_t month);
	void setDay(const size_t day);
	// void setTime(const Time& time);

	size_t getYear() const;
	size_t getMonth() const;
	size_t getDay() const;
	// const Time& getTime() const;
	void goToNextDay();

	bool operator==(const Date& other) const;
	bool operator!=(const Date& other) const;
	bool operator>(const Date& other) const;
	bool operator<(const Date& other) const;

	friend ostream& operator<<(ostream& out, const Date& date); // for console
	friend istream& operator>>(istream& in, Date& time); // for console
	friend ofstream& operator<<(ofstream& out, const Date& date); // for file
	friend ifstream& operator>>(ifstream& in, Date& time); // for file
};
