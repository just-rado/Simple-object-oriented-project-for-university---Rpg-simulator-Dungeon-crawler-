#include "Item.h"
#include "Classes.h"
#include <stdexcept>
#include <iostream>

uint64_t Item::nextId = 0;

Item::Item(const ItemData& data) : id(nextId), name(data.name), rarity(data.rarity), type(data.type) , costInGoldCoins(data.costInGoldCoins), 
weightInKg(data.weightInKg), requiredLevel(data.requiredLevel), compatibleClasses(data.compatibleClasses)
{
	if (name.empty())
	{
		throw std::invalid_argument("Name cannot be empty");
	}
	else if (weightInKg < 0)
	{
		throw std::invalid_argument("Weight cannot be negative");
	}
	else if (compatibleClasses.size() != optimalSizeOfVector())
	{
		throw std::invalid_argument("Invalid size of vector");
	}
	nextId++;
}

Item::Item(const Item& other) : id(nextId), name(other.name), rarity(other.rarity), type(other.type) , costInGoldCoins(other.costInGoldCoins) , 
		weightInKg(other.weightInKg), requiredLevel(other.requiredLevel), compatibleClasses(other.compatibleClasses)
{
	++nextId;
}

void Item::setTypeOfItem(TypeOfItem type)
{
	this->type = type;
}

void Item::printInfo()const
{

	std::cout << "Name: " << this->name << '\n' << "Id: " << this->id << '\n'
		<< "Rarity: ";
	printRarity();
	std::cout << "Cost: " << this->costInGoldCoins << '\n' << "Weight: " << this->weightInKg << "kg\n"
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
float Item::getWeight()const
{
	return this->weightInKg;
}
unsigned int Item::getCost()const
{
	return this->costInGoldCoins;
}
Rarity Item::getRarity()const
{
	return this->rarity;
}
TypeOfItem Item::getTypeOfItem()const
{
	return this->type;
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

size_t Item::optimalSizeOfVector()const
{
	size_t size = 1;
	while (true)
	{
		if (size * CLASSES_PER_UINT64 >= getAmountOfHeroClasses())
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
		if (i >= CLASSES_PER_UINT64)
		{
			++index;
		}
		find = one << (i % CLASSES_PER_UINT64);
		find = (find & this->compatibleClasses[index]);
		if (find != 0)
		{
			printHeroClass(static_cast<HeroClass>(i));
		}
	}
}


