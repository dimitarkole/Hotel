#pragma warning(disable:4996)
#include "Time.h"
#include<iostream>
#include<fstream>
using namespace std;

Time::Time(size_t hours, size_t mins){//, size_t secs) {
	setHours(hours);
	setMins(mins);
	// setSecs(secs);
}

void Time::setHours(size_t hours) {
	this->hours = hours % 24;
}

void Time::setMins(size_t mins) {
	if (mins >= 60) {
		setHours(hours + mins / 60);
		mins = mins % 60;
	}

	this->mins = mins;
}

/*void Time::setSecs(size_t secs) {
	if (secs >= 60) {
		setMins(mins + secs / 60);
		secs = secs % 60;
	}

	this->secs = secs;
}*/

size_t Time::getHours() {
	return hours;
}

size_t Time::getMins() {
	return mins;
}

/*size_t Time::getSecs() {
	return secs;
}*/

size_t Time::convertToMins() const {
	return hours * 3600 + mins * 60;// +secs;
}

ofstream& operator<<(ofstream& out, const Time& time) {
	const char dots = ':';
	out.write((const char*)&time.hours, sizeof(time.hours));
	out.write((const char*)&dots, sizeof(dots));
	out.write((const char*)&time.mins, sizeof(time.mins));
	// out.write((const char*)&dots, sizeof(dots));
	// out.write((const char*)&time.secs, sizeof(time.secs));
	return out;
}

ostream& operator<<(ostream& out, const Time& time) {
	const char dots = ':';
	out << time.hours << dots << time.mins;// << dots << time.secs;
	return out;
}

ifstream& operator>>(ifstream& in, Time& time) {
	char dots = ':';
	size_t hours, mins; // , secs;
	in.read((char*)&hours, sizeof(hours));
	in.read((char*)&dots, sizeof(dots));
	in.read((char*)&mins, sizeof(mins));
	// in.read((char*)&dots, sizeof(dots));
	// in.read((char*)&secs, sizeof(secs));
	time.setHours(hours);
	time.setMins(mins);
	// time.setSecs(secs);
	return in;
}

istream& operator>>(istream& in, Time& time) {
	char dots = ':';
	size_t hours, mins;// , secs;
	in >> hours >> mins; // >> secs;
	time.setHours(hours);
	time.setMins(mins);
	// time.setSecs(secs);
	return in;
}

bool Time::operator==(const Time& other) const {
	return this->mins == other.mins
		&& this->hours == other.hours;
		// && this->secs == other.secs;
}

bool Time::operator!=(const Time& other) const {
	return !(*this == other);
}

bool Time::operator<=(const Time& other) const {
	if (hours < other.hours) return true;
	else if (hours == other.hours) {
		if (mins <= other.mins) return true;
	}

	return false;
}

bool Time::operator>=(const Time& other) const {
	if (hours > other.hours) return true;
	else if (hours == other.hours) {
		if (mins >= other.mins) return true;
	}

	return false;
}
