#include "Item.h"
#include "Classes.h"
#include <stdexcept>
#include <iostream>

uint64_t Item::nextId = 0;

Item::Item(const ItemData& data) : id(nextId), name(data.name), rarity(data.rarity), cost(data.cost), 
weightInKg(data.weightInKg), requiredLevel(data.requiredLevel), compatibleClasses(data.compatibleClasses)
{
	if (name.empty())
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
	else if (compatibleClasses.size() > optimalSizeOfVector())
	{
		throw std::invalid_argument("Maximum amout of classes is 255");
	}
	nextId++;
}

Item::Item(const Item& other) : id(nextId), name(other.name), rarity(other.rarity), cost(other.cost) , 
		weightInKg(other.weightInKg), requiredLevel(other.requiredLevel), compatibleClasses(other.compatibleClasses)
{
	++nextId;
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

size_t Item::optimalSizeOfVector()
{
	size_t size = 1;
	while (true)
	{
		if (size * MAX_AMOUNT_OF_ClASSES_STORED_INSIDE_UINT64 >= getAmountOfHeroClasses())
		{
			return size;
		}
		++size;
	}
	return size;
}

void Item::printCompatibleClasses()const
{
	uint64_t one = 1;
	uint64_t find = 0;

	size_t index = 0;
	size_t size = getAmountOfHeroClasses();
	for (size_t i = 0; i < size; ++i)
	{
		if (size >= MAX_AMOUNT_OF_ClASSES_STORED_INSIDE_UINT64)
		{
			++index;
		}
		find = one << (i % MAX_AMOUNT_OF_ClASSES_STORED_INSIDE_UINT64);
		find = (find & this->compatibleClasses[index]);
		if (find != 0)
		{
			printHeroClass(static_cast<HeroClass>(i));
		}
	}
}


void Item::getBackId()
{
	--nextId;
}