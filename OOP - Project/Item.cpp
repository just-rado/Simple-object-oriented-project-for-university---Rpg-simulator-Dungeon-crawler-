#include "Item.h"
#include "Classes.h"
#include <stdexcept>
#include <iostream>

uint64_t Item::nextId = 0;

Item::Item(const std::string& name, Rarity rarity, float cost, float weightInKg,
	unsigned int requiredLevel, const std::vector<uint64_t>& compatibleClasses) : id(0) , name(name) ,
	rarity(rarity), cost(cost) , weightInKg(weightInKg) , requiredLevel(requiredLevel) , compatibleClasses(compatibleClasses)
{
	if (name.empty() )
	{
		throw std::invalid_argument("Name cannot be empty");
	}
	else if (cost < 0)
	{
		throw std::invalid_argument("Cost cannot be negative");
	}
	else if (weightInKg < 0)
	{
		throw std::invalid_argument("Weight cannot be negative");
	}
	else if (compatibleClasses.size() * Item::MAX_AMOUNT_OF_ClASSES_STORED_INSIDE_UINT64 > UINT8_MAX + 1)
	{
		throw std::invalid_argument("Maximum amout of classes is 255");
	}
	this->id = nextId++;
}

void Item::printInfo()const
{

	std::cout << "Name: " << this->name << '\n' << "Id: " << this->id << '\n'
		<< "Rarity: ";
	printRarity();
	std::cout << "Cost: " << this->cost << '\n' << "Weight: " << this->weightInKg << "kg\n"
		<< "Required level: " << this->requiredLevel << '\n';
	printCompatibleClasses();

}

uint64_t Item::getId()const
{
	return this->id;
}
const std::string& Item::getName()const
{
	return this->name;
}
Rarity Item::getRarity()const
{
	return this->rarity;
}
unsigned int Item::getRequiredLevel()const
{
	return requiredLevel;
}
const std::vector<uint64_t>& Item::getCompatibleClasses()const
{
	return this->compatibleClasses;
}

void Item::printRarity()const
{
	switch (this->rarity)
	{
	case Rarity::COMMON: 
		std::cout << "Common\n"; 
		break;

	case Rarity::RARE: 
		std::cout << "Rare\n";
		break;

	case Rarity::EPIC:
		std::cout << "Epic\n";
		break;

	case Rarity::LEGENDARY:
		std::cout << "Legendary\n";
		break;

	default: 
		std::cout << "Unknown rarity'\n";
		break;
	}
}

void Item::printCompatibleClasses()const
{
	
}
