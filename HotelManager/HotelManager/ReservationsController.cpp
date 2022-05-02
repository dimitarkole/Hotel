#pragma warning(disable:4996)
#include "ReservationsController.h"
#include<iostream>
#include<fstream>
using namespace std;

void ReservationsController::readFromFile(char* fileName) {
	ifstream file(fileName, ios::binary);
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

void ReservationsController::writeToFile(char* fileName) const {
	ofstream file(fileName, ios::binary);
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
void ReservationsController::writeToConsole(char* fileName) const {
	cout << reservationsService;
}