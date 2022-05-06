#pragma once
#pragma once
#pragma warning(disable:4996)

#include "CloseRoomsService.h"

class CloseRoomsController
{
private:
	CloseRoomsService closeRoomsService;
	void readFromFile();
public:
	CloseRoomsController();

	void readFromConsole();
	void closeRoom();
	void writeToFile() const;
	void writeToConsole() const;
};
