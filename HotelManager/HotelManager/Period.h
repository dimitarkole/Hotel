#pragma once
#include<iostream>
#include "Date.h"
using namespace std;

class Period
{
private:
	Date from, to;
public:
	Period();
	Period(const Period& other);
	Period(const Date& from, const Date& to);

	const Date& getFrom() const;
	const Date& getTo() const;

	void setFrom(const Date& from);
	void setTo(const Date& to);

	Period& operator=(const Period& other);

	friend ostream& operator<<(ostream& out, const Period& period); // for console
	friend istream& operator>>(istream& in, Period& period); // for console
	friend ofstream& operator<<(ofstream& out, const Period& period); // for file
	friend ifstream& operator>>(ifstream& in, Period& period); // for file
};
