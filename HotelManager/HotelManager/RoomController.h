#pragma once
#pragma warning(disable:4996)
#include "RoomsService.h"
class RoomController
{
private: 
	RoomsService roomsService;
public:
	// void add();
	void readFromFile(char* fileName);
	void readFromConsole();
	void writeToFile(char* fileName) const;
	void writeToConsole(char* fileName) const;
	// void remove(size_t id);
	// void edit(size_t id, Room& room);
};
