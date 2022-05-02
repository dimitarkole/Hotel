#pragma warning(disable:4996)
#include "Date.h"
#include "Time.h"
#include<fstream>
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

size_t Date::getYear() const {
	return year;
}

size_t Date::getMonth() const {
	return month;
}

size_t Date::getDay() const {
	return day;
}

const Time& Date::getTime() const {
	return time;
}

Date::Date(const size_t year, const size_t month, const size_t day, const size_t hours,	const size_t mins, const size_t secs) {
	this->year = year;
	this->month = month;
	this->day = day;
	this->time.setHours(hours);
	this->time.setMins(mins);
	// this->time.setSecs(secs);
}

ostream& operator<<(ostream& out, const Date& date) { // for console
	out << date.day << "/"<< date.month <<"/" << date.year << " "<< date.time;
	return out;
}

ofstream& operator<<(ofstream& out, const Date& date) { // for file
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

ifstream& operator>>(ifstream& in, Date& date) {
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

istream& operator>>(istream& in, Date& date) { // for console
	size_t day, month, year;
	Time time;
	in >> day >> month >> year >> time;
	date.setDay(day);
	date.setMonth(month);
	date.setYear(year);
	date.setTime(time);
	return in;
}

bool Date::operator==(const Date& other) {
	return this->day == other.day
		&& this->month == other.month
		&& this->year == other.year
		&& this->time == other.time;
}

bool Date::operator!=(const Date& other) {
	return ! (*this == other);
}
