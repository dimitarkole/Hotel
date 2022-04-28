#pragma once
#include<iostream>
#include "Reservation.h"
using namespace std;
class ReservationService
{
private:
	Reservation **reservations;
	size_t capacity, reservationsCount;
	void free();
	void resize();
	void copyFrom(const ReservationService& other);
public:
	ReservationService();
	ReservationService(const ReservationService& other);
	~ReservationService();
	ReservationService& operator=(const ReservationService& other);
	const Reservation* operator[](const size_t index)const;
	Reservation* operator[](const size_t index);

	const Reservation** getReservations() const;
	const size_t getCapacity() const;
	const size_t getReservationsCount() const;

	void addReservation(const Reservation& reservation);

	friend ostream& operator<<(ostream& out, const ReservationService& reservation);
	friend ofstream& operator<<(ofstream& out, const ReservationService& reservation);
	friend istream& operator>>(istream& in, ReservationService& reservation);
	friend ifstream& operator>>(ifstream& in, ReservationService& reservation);
};
