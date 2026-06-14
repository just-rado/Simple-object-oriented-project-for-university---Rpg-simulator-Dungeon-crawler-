#include "Room.h"
#include <stdexcept>

Room::Room(const std::string& name, const std::vector<Enemy*>& enemies, const std::vector<Item*>& items) : name(name)
{
	if (name.empty())
	{
		throw std::invalid_argument("Must have a name");
	}

	handleHeapMemory(enemies, items);
}
Room::Room(const Room& other) : name(other.name)
{
	handleHeapMemory(other.enemies, other.items);
}
Room::~Room()
{
	deleteVectorPointers(this->enemies);
	deleteVectorPointers(this->items);
}

size_t Room::getNumberOfEnemies()const
{
	return this->enemies.size();
}
size_t Room::getNumberOfItems()const
{
	return this->items.size();
}


Enemy& Room::getEnemy(size_t index)const
{
	return *this->enemies[index];
}
Item& Room::getItem(size_t index)const
{
	return *this->items[index];
}


bool Room::isEmpty()const
{
	return this->enemies.empty() && this->items.empty();
}

void Room::handleHeapMemory(const std::vector<Enemy*>& enemies ,const std::vector<Item*>& items)
{
	size_t numberOfEntities = enemies.size();
	for (size_t i = 0; i < numberOfEntities; ++i)
	{
		Enemy* toPush = nullptr;
		try
		{
			toPush = enemies[i]->clone();
			this->enemies.push_back(toPush);
		}
		catch (...)
		{
			delete toPush;
			deleteVectorPointers(this->enemies);
			throw;
		}
			
	}

	numberOfEntities = items.size();
	for (size_t i = 0; i < numberOfEntities; ++i)
	{
		Item* toPush = nullptr;
		try
		{
			toPush = items[i]->clone();
			this->items.push_back(toPush);
		}
		catch (...)
		{
			delete toPush;
			deleteVectorPointers(this->enemies);
			deleteVectorPointers(this->items);
			throw;
		}
	}
}

