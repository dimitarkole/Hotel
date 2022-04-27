#include "Date.h"
#include "Time.h"
#include<iostream>
using namespace std;

void Date::setYear(const size_t year) {
	this->year = year;
}
void Date::setMonth(const size_t month) {
	this->month;
}
void Date::setDay(const size_t day) {
	this->day = day;
}

void Date::setTime(const Time& time) {
	this->time = time;
}

Date::Date(const size_t year = 0, const size_t month = 0, const size_t day = 0,
		const size_t hours = 0, const size_t mins = 0, const size_t secs = 0) {
	this->year = year;
	this->month = month;
	this->day = day;
	this->time.setHours(hours);
	this->time.setMins(mins);
	this->time.setSecs(secs);
}

ostream& operator<<(ostream& out, const Date& date) {
	const char slash = '/', whiteSpace = ' ';
	out.write((const char*)&date.day, sizeof(date.day));
	out.write((const char*)&slash, sizeof(slash));
	out.write((const char*)&date.month, sizeof(date.month));
	out.write((const char*)&slash, sizeof(slash));
	out.write((const char*)&date.year, sizeof(date.year));
	out.write((const char*)&whiteSpace, sizeof(whiteSpace));
	out << date.time;
	return out;
}

istream& operator>>(istream& in, Date& date) {
	char slash = '/', whiteSpace = ' ';
	size_t day, month, year;
	in.read((char*)&day, sizeof(day));
	in.read((char*)&slash, sizeof(slash));
	in.read((char*)&month, sizeof(month));
	in.read((char*)&slash, sizeof(slash));
	in.read((char*)&year, sizeof(year));
	in.read((char*)&whiteSpace, sizeof(whiteSpace));
	date.setYear(year);
	date.setMonth(month);
	date.setDay(day);
	Time time;
	in >> time;
	date.setTime(time);
	return in;
}