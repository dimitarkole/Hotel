#pragma warning(disable:4996)
#include "ReservationsController.h"
#include<iostream>
#include<fstream>
using namespace std;

const char* RESERVATION_FILE_NAME = "reservations.dat";

ReservationsController::ReservationsController()
{
	readFromFile();
}

void ReservationsController::readFromFile() {
	ifstream file(RESERVATION_FILE_NAME, ios::binary);
	if (!file.is_open()) {
		return;
	}

	file >> reservationsService;
	try
	{
		file.close();
	}
	catch (const std::exception&)
	{
	}
}

void ReservationsController::readFromConsole() {
	cin >> reservationsService;
}

void ReservationsController::writeToFile() const {
	ofstream file(RESERVATION_FILE_NAME, ios::binary);
	if (!file.is_open()) {
		return;
	}

	file << reservationsService;
	try
	{
		file.close();
	}
	catch (const std::exception&)
	{
	}
}
void ReservationsController::writeToConsole() const {
	cout << reservationsService;
}