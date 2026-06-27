#include "Room.h"
#include <stdexcept>
#include "StringFunctionsForFiles.h"
#include "Skeleton.h"
#include "Werewolf.h"
#include "Armor.h"
#include "Weapon.h"
#include "Relic.h"
#include "Scroll.h"
#include "Consumable.h"
#include <iostream>

Room::Room(const std::string& name, const std::vector<Enemy*>& enemies, const std::vector<Item*>& items) : name(name)
{
	if (name.empty())
	{
		throw std::invalid_argument("Must have a name");
	}

	handleHeapMemory(enemies, items);
}

Room::Room(std::ifstream& read): name(readString(read))
{
	uint32_t numberOfEnemies = 0;
	read.read(reinterpret_cast<char*>(&numberOfEnemies), sizeof(numberOfEnemies));
	try
	{
		if (numberOfEnemies > 0)
		{
			this->enemies.resize(numberOfEnemies);

			for (uint32_t i = 0; i < numberOfEnemies; ++i)
			{
				uint32_t typeOfEnemyValue = 0;
				read.read(reinterpret_cast<char*>(&typeOfEnemyValue), sizeof(typeOfEnemyValue));

				TypeOfEnemy type = static_cast<TypeOfEnemy>(typeOfEnemyValue);
				switch (type)
				{
				case TypeOfEnemy::SKELETON:
					this->enemies[i] = new Skeleton(read);
					break;
				case TypeOfEnemy::WEREWOLF:
					this->enemies[i] = new Werewolf(read);
					break;
				default:
					throw std::runtime_error("Error");
				}
			}
		}

		uint32_t numberOfItems = 0;
		read.read(reinterpret_cast<char*>(&numberOfItems), sizeof(numberOfItems));

		if (numberOfItems > 0)
		{
			this->items.resize(numberOfItems);

			for (uint32_t i = 0; i < numberOfItems; ++i)
			{
				uint32_t typeOfItemValue = 0;
				read.read(reinterpret_cast<char*>(&typeOfItemValue), sizeof(typeOfItemValue));

				TypeOfItem type = static_cast<TypeOfItem>(typeOfItemValue);

				uint64_t ID = 0;
				read.read(reinterpret_cast<char*>(&ID), sizeof(ID));

				switch (type)
				{
				case TypeOfItem::WEAPON:
					this->items[i] = new Weapon(read, ID);
					break;
				case TypeOfItem::ARMOR:
					this->items[i] = new Armor(read, ID);
					break;
				case TypeOfItem::CONSUMABLE:
					this->items[i] = new Consumable(read, ID);
					break;
				case TypeOfItem::SCROLL:
					this->items[i] = new Scroll(read, ID);
					break;
				case TypeOfItem::RELIC:
					this->items[i] = new Relic(read, ID);
					break;
				default:
					throw std::runtime_error("Error");
				}
			}

		}
	}
	catch (...)
	{
		size_t getActualEnemyCount = this->enemies.size();
		for (size_t i = 0; i < getActualEnemyCount; ++i)
		{
			delete this->enemies[i];

		}
		this->enemies.clear();

		size_t getActualItemCount = this->items.size();
		for (size_t i = 0; i < getActualItemCount; ++i)
		{
			delete this->items[i];
		}
		this->items.clear();
	
		throw;
	}
	
	
}
void Room::writeToFile(std::ofstream& write)const
{
	writeString(write, this->name);

	uint32_t numberOfEnemies = static_cast<uint32_t>(this->enemies.size());
	write.write(reinterpret_cast<const char*>(&numberOfEnemies), sizeof(numberOfEnemies));

	for (uint32_t i = 0; i < numberOfEnemies; ++i)
	{
		this->enemies[i]->writeToFile(write);
	}

	uint32_t numberOfItems = static_cast<uint32_t>(this->items.size());
	write.write(reinterpret_cast<const char*>(&numberOfItems), sizeof(numberOfItems));

	for (uint32_t i = 0; i < numberOfItems; ++i)
	{
		this->items[i]->writeDataToFile(write);
	}
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

const std::string& Room::getNameOfroom()const
{
	return this->name;
}
size_t Room::getNumberOfEnemies()const
{
	return this->enemies.size();
}
size_t Room::getNumberOfItems()const
{
	return this->items.size();
}


Enemy* Room::getEnemy(size_t index)const
{
	return this->enemies[index];
}
Item* Room::getItem(size_t index)const
{
	return this->items[index];
}


bool Room::isEmpty()const
{
	return this->enemies.empty() && this->items.empty();
}

void Room::handleHeapMemory(const std::vector<Enemy*>& enemies ,const std::vector<Item*>& items)
{
	size_t numberOfEntities = enemies.size();
	Enemy* toPush = nullptr;
	try
	{
		for (size_t i = 0; i < numberOfEntities; ++i)
		{		
				toPush = enemies[i]->clone();
				this->enemies.push_back(toPush);	
		}
	}
	catch(...)
	{
		delete toPush;
		deleteVectorPointers(this->enemies);
		throw;
	}
	

	numberOfEntities = items.size();
	Item* toPushItem = nullptr;
	try
	{
		for (size_t i = 0; i < numberOfEntities; ++i)
		{
			toPushItem = items[i]->clone();
			this->items.push_back(toPushItem);
		}
	}
	catch (...)
	{
		std::cout << "second";
		delete toPushItem;
		deleteVectorPointers(this->enemies);
		deleteVectorPointers(this->items);
	}
	
}

