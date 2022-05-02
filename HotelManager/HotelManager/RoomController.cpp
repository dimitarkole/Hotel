#pragma warning(disable:4996)
#include "RoomController.h"
#include<iostream>
#include<fstream>
using namespace std;

void RoomController::readFromFile(char* fileName) {
	ifstream file(fileName, ios::binary);
	if (!file.is_open()) {
		return;
	}

	file >> roomsService;
	try
	{
		file.close();
	}
	catch (const std::exception&)
	{
	}
}

void RoomController::readFromConsole() {
	cin >> roomsService;
}

void RoomController::writeToFile(char* fileName) const {
	ofstream file(fileName, ios::binary);
	if (!file.is_open()) {
		return;
	}

	file << roomsService;
	try
	{
		file.close();
	}
	catch (const std::exception&)
	{
	}
}
void RoomController::writeToConsole(char* fileName) const {
	cout << roomsService;
}