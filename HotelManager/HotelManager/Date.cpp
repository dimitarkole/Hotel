#pragma warning(disable:4996)
#include "Date.h"
//#include "Time.h"

bool Date::isLeapYear() const
{
	if (year <= 1916)
		return year % 4 == 0;
	return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

void Date::validateDateByChangedCalendars()
{
	if (year == 1916 && month == 4 && day >= 1 && day <= 13) // invalid days due to change in callendars 
		day = 15;
}

void Date::setYear(size_t year)
{
	this->year = year;

	if (isLeapYear())
		MAX_DAYS[1] = 29;
	else
		MAX_DAYS[1] = 28;
	isModified = true;
	validateDateByChangedCalendars();
}

void Date::setMonth(size_t month)
{
	if (month > 12)
	{
		month = 1;
	}
	this->month = month;

	if (day > MAX_DAYS[month - 1])
		day = MAX_DAYS[month - 1];

	isModified = true;
	validateDateByChangedCalendars();
}

void Date::setDay(size_t day)
{
	if (day > MAX_DAYS[month - 1])
	{
		day = 1;
	}
	this->day = day;
	isModified = true;
	validateDateByChangedCalendars();
}

void Date::goToNextDay()
{
	if (areEqual(Date(31, 03, 1916)))
	{
		setDay(14);
		setMonth(04);
		return;
	}

	setDay(day + 1);
	if (day == 1)
	{
		setMonth(month + 1);
		if (month == 1)
			setYear(year + 1);
	}
}

bool Date::areEqual(const Date& other) const
{
	return year == other.year && month == other.month && day == other.day;
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

/*const Time& Date::getTime() const {
	return time;
}*/

Date::Date(const size_t year, const size_t month, const size_t day)//const size_t hours,	const size_t mins, const size_t secs) {
{
	setYear(year);
	setMonth(month);
	setDay(day);
}

ostream& operator<<(ostream& out, const Date& date) { // for console
	out << date.getDay() << "/" << date.getMonth()  << "/" << date.getYear();//<< " "<< date.time;
	return out;
}

ofstream& operator<<(ofstream& out, const Date& date) { // for file
	size_t day = date.getDay(), month = date.getMonth(), year = date.getYear();
	out.write((const char*)&day, sizeof(day));
	out.write((const char*)&month, sizeof(month));
	out.write((const char*)&year, sizeof(year));
	// out << date.time;
	return out;
}

ifstream& operator>>(ifstream& in, Date& date) {
	size_t day, month, year;
	in.read((char*)&day, sizeof(day));
	in.read((char*)&month, sizeof(month));
	in.read((char*)&year, sizeof(year));
	date.setYear(year);
	date.setMonth(month);
	date.setDay(day);
	// Time time;
	// in >> time;
	// date.setTime(time);
	return in;
}

istream& operator>>(istream& in, Date& date) { // for console
	size_t day, month, year;
	//Time time;
	in >> day >> month >> year;//>> time;
	date.setYear(year);
	date.setMonth(month);
	date.setDay(day);
	//date.setTime(time);
	return in;
}

bool Date::operator==(const Date& other) const {
	return this->day == other.day
		&& this->month == other.month
		&& this->year == other.year;
		//&& this->time == other.time;
}

bool Date::operator!=(const Date& other) const {
	return ! (*this == other);
}

bool Date::operator>(const Date& other) const {
	if (year > other.year) return true;
	else if(year == other.year){
		if (month > other.month) return true;
		else if (month == other.month) {
			if (day > other.day) return true;
			/*else if (day == other.day)
			{
				return time >= other.time;
			}*/
		}
	}

	return false;
}

bool Date::operator>=(const Date& other) const {
	if (year > other.year) return true;
	else if (year == other.year) {
		if (month > other.month) return true;
		else if (month == other.month) {
			if (day >= other.day) return true;
			/*else if (day == other.day)
			{
				return time >= other.time;
			}*/
		}
	}

	return false;
}


bool Date::operator<(const Date& other) const {
	if (year < other.year) return true;
	else if (year == other.year) {
		if (month < other.month) return true;
		else if (month == other.month) {
			if (day < other.day) return true;
			/*else if (day == other.day)
			{
				return time <= other.time;
			}*/
		}
	}

	return false;
}

bool Date::operator<=(const Date& other) const {
	if (year < other.year) return true;
	else if (year == other.year) {
		if (month < other.month) return true;
		else if (month == other.month) {
			if (day <= other.day) return true;
			/*else if (day == other.day)
			{
				return time <= other.time;
			}*/
		}
	}

	return false;
}
