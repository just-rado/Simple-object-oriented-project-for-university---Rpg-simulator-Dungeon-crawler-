#include "Dungeon.h"
#include "StringFunctionsForFiles.h"
#include <iostream>

Dungeon::Dungeon(const std::string& name , size_t level) : name(name) , level(level)  , currentRoom(0) , rooms()
{
}


Dungeon::Dungeon(std::ifstream& read)
{
	this->name = readString(read);
	
	read.read(reinterpret_cast<char*>(&this->level), sizeof(this->level));

	this->currentRoom = 0;

	uint32_t numberOfRooms = 0;
	read.read(reinterpret_cast<char*>(&numberOfRooms), sizeof(numberOfRooms));

	this->rooms.resize(numberOfRooms);
	size_t allocated = 0;
	try
	{
		for (uint32_t i = 0; i < numberOfRooms; ++i)
		{	
			this->rooms[i] = new Room(read);
			++allocated;
		}
	}
	catch (...)
	{
		freeAllocatedMemory(this->rooms, allocated);
		throw;
	}

	
	if (!read)
	{
		throw std::runtime_error("Error");
	}


}

void Dungeon::writeDataToFile(std::ofstream& write)const
{
	writeString(write, this->name);

	write.write(reinterpret_cast<const char*>(&this->level), sizeof(level));

	uint32_t numberOfRooms = this->rooms.size();
	write.write(reinterpret_cast<const char*>(&numberOfRooms), sizeof(numberOfRooms));

	for (size_t i = currentRoom; i < numberOfRooms; ++i)
	{
		if (!write)
		{
			throw std::runtime_error("Error");
		}

		this->rooms[i]->writeToFile(write);
	}
}

void Dungeon::addRoomToDungeon(const Room& room)
{
	Room* toCopy = new (std::nothrow) Room(room);
	if (!toCopy)
	{
		std::cout << "Could not add room\n";
		return;
	}

	try
	{
		this->rooms.push_back(toCopy);
	}
	catch (...)
	{
		delete toCopy;
		std::cout << "Could not add room\n";
		return;
	}

	std::cout << "Added room\n";
}

size_t Dungeon::getNumberOfRooms()const
{
	return this->rooms.size();
}

void Dungeon::nextRoom()
{
	++this->currentRoom;
}

void Dungeon::freeAllocatedMemory(std::vector<Room*>& rooms, size_t allocated)
{
	for (size_t i = 0; i < allocated; ++i)
	{
		delete rooms[i];
		rooms[i] = nullptr;
	}
}
void Dungeon::copyHeap(std::vector<Room*>& copy, const std::vector<Room*>& original)
{
	if (copy.size() != original.size())
	{
		throw std::invalid_argument("Error");
	}

	size_t allocated = 0;
	try
	{
		size_t numberOfRooms = copy.size();
		for (size_t i = 0; i < numberOfRooms; ++i)
		{
			copy[i] = new Room(*original[i]);
			++allocated;
		}
	}
	catch (...)
	{
		freeAllocatedMemory(copy, allocated);
		throw;
	}
}

Dungeon::Dungeon(const Dungeon& other)
{
	this->rooms.resize(other.rooms.size());
	copyHeap(this->rooms, other.rooms);

	this->name = other.name;
	this->level = other.level;
	this->currentRoom = other.currentRoom;
	
}
Dungeon& Dungeon::operator=(const Dungeon& other)
{
	if (this != &other)
	{
		std::string newName = other.name;
		std::vector<Room*> copy;
		copy.resize(other.rooms.size());
		copyHeap(copy, other.rooms);
		
		freeAllocatedMemory(this->rooms, this->rooms.size());

		this->rooms = std::move(copy);
		this->name = std::move(newName);
		this->level = other.level;
		this->currentRoom = other.currentRoom;
	}
	return *this;
}
Dungeon::~Dungeon()
{
	freeAllocatedMemory(this->rooms, this->rooms.size());
}

const std::string& Dungeon::getNameOfDungeon()const
{
	return this->name;
}
Room* Dungeon::getCurrentRoom()const
{
	if (this->currentRoom < this->rooms.size())
	{
		return this->rooms[currentRoom];
	}

	return nullptr;
}

void Dungeon::printInfo()const
{
	std::cout << "Name of dungeon: " << this->name << '\n';
	std::cout << "Level of dungeon: " << this->level << '\n';
	std::cout << "Number of rooms: " << this->rooms.size() << '\n';
}


