#include "Room.h"
Room::Room(): Room(0,0) {
}

Room::Room(const size_t id, const size_t bedsCount) {
	setId(id);
	setBedsCount(bedsCount);
}

size_t Room::getId() const {
	return id;
}

size_t Room::getBedsCount() const {
	return bedsCount;
}

void Room::setId(const size_t id) {
	this->id = id;
}

void Room::setBedsCount(const size_t bedsCount) {
	this->bedsCount = bedsCount;
}