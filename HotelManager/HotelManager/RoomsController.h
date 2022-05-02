#pragma once
#pragma warning(disable:4996)
#include "RoomsService.h"
class RoomsController
{
private: 
	RoomsService roomsService;
public:
	RoomsController();
	// RoomsController();
	// void add();
	void readFromFile();
	void readFromConsole();
	void writeToFile() const;
	void writeToConsole() const;
	// void remove(size_t id);
	// void edit(size_t id, Room& room);
};
