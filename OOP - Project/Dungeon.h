#pragma once
#include <string>
#include "Room.h"
#include <fstream>
class Dungeon
{
public:

	Dungeon(const std::string& name, const Room* room);

	Dungeon(std::ifstream& read);
	bool loadNextRoom(std::ifstream& file);
	void writeNameToFile(std::ofstream& write)const;
	void writeCurrentRoomToFile(std::ofstream& write)const;

	Dungeon(const Dungeon& other);
	Dungeon& operator=(const Dungeon& other);
	~Dungeon();


	const std::string& getNameOfDungeon()const;
	const Room* getCurrentRoom()const;

private:
	std::string name;
	
	std::streampos position;
	Room* currentRoom;

};

