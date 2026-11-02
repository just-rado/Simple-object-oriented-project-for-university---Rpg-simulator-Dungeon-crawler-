#pragma once
#include <string>
#include "Room.h"
#include <fstream>
#include <vector>
#include "Hero.h"
class Dungeon
{
public:

	Dungeon(const std::string& name , size_t level);

	Dungeon(std::ifstream& read);

	void addRoomToDungeon(const Room& room);

	void writeDataToFile(std::ofstream& write)const;

	Dungeon(const Dungeon& other);
	Dungeon& operator=(const Dungeon& other);
	~Dungeon();

	void printInfo()const;

	const std::string& getNameOfDungeon()const;
	Room* getCurrentRoom()const;
	size_t getNumberOfRooms()const;

	void nextRoom();
	

private:
	std::string name;
	size_t level;
	size_t currentRoom;
	
	std::vector<Room*> rooms;

	static void freeAllocatedMemory(std::vector<Room*>& rooms, size_t allocated);
	static void copyHeap(std::vector<Room*>& copy ,const std::vector<Room*>& original);

};

