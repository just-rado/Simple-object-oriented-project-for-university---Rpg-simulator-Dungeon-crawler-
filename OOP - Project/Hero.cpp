#include "Hero.h"
#include <stdexcept>
Hero::Information::Information()
{
	this->battle = nullptr;
	this->statsAfterBattle = CharacterStats();
}

bool Hero::Information::addBattle(const std::string& nameOfRoom, const std::vector<std::string>& namesOfHeroes, 
							const std::vector<uint64_t>& IDsOfEnemies)
{

	this->battle = new (std::nothrow) Battle(nameOfRoom, namesOfHeroes, IDsOfEnemies);
	if (!this->battle)
	{
		return false;
	}
	return true;
}
void Hero::Information::addStatsAfterBattle(const CharacterStats& stats)
{
	this->statsAfterBattle = stats;
}

Hero::Information::~Information()
{
	delete this->battle;
	this->battle = nullptr;
}



Hero::Hero(const CharacterData& mainStats): Character(mainStats)
{}
Hero::Hero(const Hero& other): Character(other)
{
	handleHeapMemory(other.inventory, other.equippedItems);	
}
Hero& Hero::operator=(const Hero& other)
{
	if (this != &other)
	{
		std::vector<Item*> toDeleteInventory = std::move(this->inventory);
		std::vector<Item*> toDeleteEquippedItems = std::move(this->equippedItems);
		handleHeapMemory(other.inventory, other.equippedItems);
		try
		{
			Character::operator=(other);
		}
		catch(...)
		{
			deleteHeapMemory(this->inventory);
			this->inventory = std::move(toDeleteInventory);

			deleteHeapMemory(this->equippedItems);
			this->equippedItems = std::move(toDeleteEquippedItems);
			
			throw;
		}
		deleteHeapMemory(toDeleteInventory);
		deleteHeapMemory(toDeleteEquippedItems);
	}
	return *this;
}
Hero::~Hero()
{
	deleteHeapMemory(this->inventory);
	deleteHeapMemory(this->equippedItems);
}



void Hero::handleHeapMemory(std::vector<Item*> inventory, std::vector<Item*> equippedItems)
{
	size_t numberOfEntities = inventory.size();
	for (size_t i = 0; numberOfEntities; ++i)
	{
		try
		{
			this->inventory.push_back(inventory[i]->clone());
		}
		catch (...)
		{
			deleteHeapMemory(this->inventory);
		}
	}
	numberOfEntities = equippedItems.size();
	for (size_t i = 0; i < numberOfEntities; ++i)
	{
		try
		{
			this->equippedItems.push_back(equippedItems[i]->clone());
		}
		catch (...)
		{
			deleteHeapMemory(this->inventory);
			deleteHeapMemory(this->equippedItems);
		}
	}
}
void Hero::deleteHeapMemory(std::vector<Item*> vector)
{
	size_t size = vector.size();
	for (size_t i = 0; i < size; ++i)
	{
		delete vector[i];
	}
	vector.clear();
}