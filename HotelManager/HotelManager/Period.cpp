#include "Period.h"

Period::Period() {
}

Period::Period(const Date& from, const Date& to) {
	setFrom(from);
	setTo(to);
}

Period::Period(const Period& period) {
	setFrom(period.from);
	setTo(period.to);
}

const Date& Period::getFrom() const {
	return from;
}

const Date& Period::getTo() const {
	return to;
}

void Period::setFrom(const Date& from) {
	this->from = from;
};

void Period::setTo(const Date& to) {
	this->to = to;
}

void Period::saveToFile(ofstream& out) const {
	out << " From: " << from;
	out << " To: " << to;
}

Period& Period::operator=(const Period& period)
{
	from = period.from;
	to = period.to;
	return *this;
}

ostream& operator<<(ostream& out, const Period& period) {
	out << " From:" << period.from;
	out << " To:" << period.to;
	return out;
}

istream& operator>>(istream& in, Period& period) {
	Date from, to;
	cout << "Input date from: " << endl;
	in >> from;
	do {
		cout << "Input date to: " << endl;
		in >> to; 
	} while (to < from);
	period.setFrom(from);
	period.setTo(to);
	return in;
}

ofstream& operator<<(ofstream& out, const Period& period) {
	out << period.from << period.to;
	return out;
}

ifstream& operator>>(ifstream& in, Period& period) {
	in >> period.from >> period.to;
	return in;
}
