#pragma once
#pragma warning(disable:4996)
#include "RoomsService.h"
class RoomsController
{
private: 
	RoomsService roomsService;
	
	void readFromFile();
public:
	RoomsController();

	void readFromConsole();
	void writeToFile() const;
	void writeToConsole() const;
	const Room* getRooms() const;
	const size_t getRoomsCount() const;
};
