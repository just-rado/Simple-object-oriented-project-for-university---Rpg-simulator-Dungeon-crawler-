#include "Item.h"
#include "Classes.h"
#include <stdexcept>
#include <iostream>
#include "StringFunctionsForFiles.h"
uint64_t Item::nextId = 1;

Item::Item(const ItemData& data , TypeOfItem type) : type(type) ,id(nextId), name(data.name), rarity(data.rarity) ,
	costInGoldCoins(data.costInGoldCoins), weightInKg(data.weightInKg), requiredLevel(data.requiredLevel), compatibleClasses(data.compatibleClasses)
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

Item::Item(std::ifstream& read , TypeOfItem type , uint64_t ID): type(type) ,  id(ID) , name(readString(read))
{
	uint32_t rarityValue = 0;
	read.read(reinterpret_cast<char*>(&rarityValue), sizeof(rarityValue));

	this->rarity = static_cast<Rarity>(rarityValue);

	read.read(reinterpret_cast<char*>(&this->costInGoldCoins), sizeof(this->costInGoldCoins));

	read.read(reinterpret_cast<char*>(&this->weightInKg), sizeof(this->weightInKg));

	read.read(reinterpret_cast<char*>(&this->requiredLevel), sizeof(this->requiredLevel));

	uint32_t size = 0;
	read.read(reinterpret_cast<char*>(&size), sizeof(size));

	if (!read)
	{
		throw std::runtime_error("Failed to read item data");
	}

	if (size == 0)
	{
		return;
	}
	
	this->compatibleClasses.resize(size);
	read.read(reinterpret_cast<char*>(this->compatibleClasses.data()), size * sizeof(uint64_t));

	if (!read)
	{
		throw std::runtime_error("Failed to read item data");
	}

}
void Item::writeDataToFile(std::ofstream& write)const
{
	uint32_t typeValue = static_cast<uint32_t>(this->type);
	write.write(reinterpret_cast<const char*>(&typeValue), sizeof(typeValue));

	write.write(reinterpret_cast<const char*>(&this->id), sizeof(this->id));

	writeString(write, this->name);

	uint32_t rarityValue = static_cast<uint32_t>(this->rarity);

	write.write(reinterpret_cast<const char*>(&rarityValue), sizeof(rarityValue));

	write.write(reinterpret_cast<const char*>(&this->costInGoldCoins), sizeof(this->costInGoldCoins));

	write.write(reinterpret_cast<const char*>(&this->weightInKg), sizeof(this->weightInKg));

	write.write(reinterpret_cast<const char*>(&this->requiredLevel), sizeof(this->requiredLevel));

	uint32_t size = this->compatibleClasses.size();

	write.write(reinterpret_cast<const char*>(&size), sizeof(size));

	if (size > 0)
	{
		write.write(reinterpret_cast<const char*>(this->compatibleClasses.data()), size * sizeof(uint64_t));
	}

	if (!write)
	{
		throw std::runtime_error("Failed to write item data");
	}

}




Item::Item(const Item& other) : type(other.type) ,  id(nextId), name(other.name), rarity(other.rarity), costInGoldCoins(other.costInGoldCoins) ,
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

void Item::applyEffectsOfItem(Character* character)const
{
	return; 
}

void Item::removeEffectsOfItem(Character* character)const
{
	return; 
}

 AugmentationType Item::getAugmentationType()const
{
	return AugmentationType::NONE;
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

bool Item::checkIfClassIsCompatible(HeroClass classOfHero)const
{
	int numberOfHeroClass = static_cast<int>(classOfHero);
	size_t index = 1;
	while (true)
	{
		if (index * CLASSES_PER_UINT64 > numberOfHeroClass)
		{
			numberOfHeroClass %= CLASSES_PER_UINT64;
			uint64_t find = 1;
			find = (find << numberOfHeroClass);
			uint64_t check = (find & this->compatibleClasses[index - 1]);

			return check;
		}
		++index;
	}
	
	return false;
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


void Item::setNextID(std::ifstream& read)
{
	read.read(reinterpret_cast<char*>(&nextId), sizeof(nextId));
	if (!read)
	{
		throw std::runtime_error("Error");
	}
}
void Item::writeNextID(std::ofstream& write)
{
	write.write(reinterpret_cast<const char*>(&nextId), sizeof(nextId));
	if (!write)
	{
		throw std::runtime_error("Error");
	}
}