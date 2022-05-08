#pragma once
#pragma warning(disable:4996)
#include<iostream>
#include "Reservation.h"
using namespace std;
class ReservationsService
{
private:
	Reservation *reservations;
	size_t capacity, reservationsCount;
	void free();
	void resize();
	void copyFrom(const ReservationsService& other);
public:
	ReservationsService();
	ReservationsService(const ReservationsService& other);
	~ReservationsService();
	ReservationsService& operator=(const ReservationsService& other);
	const Reservation& operator[](const size_t index)const;
	Reservation& operator[](const size_t index);

	const Reservation* getReservations() const;
	const size_t getCapacity() const;
	const size_t getReservationsCount() const;
	void remove(size_t reservationId);

	bool isRoomFree(size_t roomId, const Date& date) const;
	bool isRoomFree(size_t roomId, const Period& period) const;
	void create(const Reservation& reservation);
	const Reservation* getReservatedRoomsForPeriod(const Period& Period, size_t& reservationsCount) const;
	bool hasReservation(size_t reservationId) const;
	friend ostream& operator<<(ostream& out, const ReservationsService& reservation);
	friend ofstream& operator<<(ofstream& out, const ReservationsService& reservation);
	friend istream& operator>>(istream& in, ReservationsService& reservation);
	friend ifstream& operator>>(ifstream& in, ReservationsService& reservation);
};
