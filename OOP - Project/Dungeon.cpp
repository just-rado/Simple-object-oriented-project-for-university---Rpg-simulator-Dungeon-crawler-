#include "Dungeon.h"
#include "StringFunctionsForFiles.h"

Dungeon::Dungeon(const std::string& name , const Room* room): name(name) ,position() ,currentRoom(nullptr)
{
	if (!room)
	{
		throw std::invalid_argument("Error");
	}
	this->currentRoom = new Room(*room);
}


Dungeon::Dungeon(std::ifstream& read)
{
	this->name = readString(read);

	bool roomExists = false;
	read.read(reinterpret_cast<char*>(&roomExists), sizeof(roomExists));

	if (roomExists)
	{
		this->currentRoom = new Room(read);
	}
	this->position = read.tellg();
	
	if (!read)
	{
		throw std::runtime_error("Error");
	}
}



Dungeon::Dungeon(const Dungeon& other)
{
	this->name = other.name;
	this->position = other.position;
	this->currentRoom = new Room(*other.currentRoom);
}
Dungeon& Dungeon::operator=(const Dungeon& other)
{
	if (this != &other)
	{
		std::string newName = other.name;

		Room* newRoom = new Room(*other.currentRoom);
		
		delete this->currentRoom;
		this->currentRoom = newRoom;

		this->name = std::move(newName);
		position = other.position;
	}
	return *this;
}
Dungeon::~Dungeon()
{
	delete this->currentRoom;
	this->currentRoom = nullptr;
}

void Dungeon::writeNameToFile(std::ofstream& write)const
{
	writeString(write, this->name);
	if (!write)
	{
		throw std::runtime_error("Error");
	}
}

void Dungeon::writeCurrentRoomToFile(std::ofstream& write)const
{
	bool exists = (this->currentRoom != nullptr);
	write.write(reinterpret_cast<const char*>(&exists), sizeof(exists));

	if (exists)
	{
		this->currentRoom->writeToFile(write);
	}

	if (!write)
	{
		throw std::runtime_error("Error");
	}
}

bool Dungeon::loadNextRoom(std::ifstream& file)
{
	file.seekg(position);

	bool roomExists = false;
	file.read(reinterpret_cast<char*>(&roomExists), sizeof(roomExists));

	if (roomExists)
	{
		Room* newRoom = new Room(file);
		
		delete this->currentRoom;
		this->currentRoom = newRoom;
		
		this->position = file.tellg();
	}
	else
	{
		this->position = file.tellg();
		
		return false;
	}
	

	if (!file)
	{
		
		throw std::runtime_error("Error");
	}
	
	return true;
}

const std::string& Dungeon::getNameOfDungeon()const
{
	return this->name;
}
const Room* Dungeon::getCurrentRoom()const
{
	return this->currentRoom;
}