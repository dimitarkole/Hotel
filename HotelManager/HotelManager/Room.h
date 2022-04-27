#pragma once
class Room
{
private:
	size_t id;
	size_t bedsCount;
public:
	Room();
	Room(const size_t id, const size_t bedsCount);

	size_t getId() const;
	size_t getBedsCount() const;

	void setId(const size_t id);
	void setBedsCount(const size_t bedsCount);
};

