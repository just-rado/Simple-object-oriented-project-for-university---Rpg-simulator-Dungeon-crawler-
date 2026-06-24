#include "Skeleton.h"
#include <random>
#include "Weapon.h"
#include "Armor.h"
#include "Consumable.h"
#include "Scroll.h"
#include "Relic.h"
Skeleton::Skeleton(const std::string& name): Enemy(createSkeletonData(name) , ENEMY_TYPE , BASE_EXP_GIVEN) , item(nullptr)
{

}

Skeleton::Skeleton(std::ifstream& read) : Enemy(read , ENEMY_TYPE)
{
	this->item = nullptr;

	bool hasItem = false;
	read.read(reinterpret_cast<char*>(&hasItem), sizeof(hasItem));

	if (hasItem)
	{
		uint32_t itemTypeValue = 0;
		read.read(reinterpret_cast<char*>(&itemTypeValue), sizeof(itemTypeValue));

		TypeOfItem type = static_cast<TypeOfItem>(itemTypeValue);

		uint64_t ID = 0;
		read.read(reinterpret_cast<char*>(&ID), sizeof(ID));
		switch (type)
		{
		case TypeOfItem::WEAPON:
			this->item = new Weapon(read, ID);

		case TypeOfItem::ARMOR:
			this->item = new Armor(read, ID);

		case TypeOfItem::CONSUMABLE:
			this->item = new Consumable(read, ID);

		case TypeOfItem::SCROLL:
			this->item = new Scroll(read, ID);

		case TypeOfItem::RELIC:
			this->item = new Relic(read, ID);
		default:
			throw std::runtime_error("Unknown item type");
		}
	}
	if (!read)
	{
		throw std::runtime_error("Error");
	}
}
void Skeleton::writeToFile(std::ofstream& write)const
{
	Enemy::writeOwnDataToFile(write);
	writeOwnDataToFile(write);
}

void Skeleton::writeOwnDataToFile(std::ofstream& write)const
{
	bool hasItem = (this->item != nullptr);
	write.write(reinterpret_cast<const char*>(&hasItem), sizeof(hasItem));

	if (hasItem)
	{
		this->item->writeDataToFile(write);
	}

	
}

Skeleton::Skeleton(const Skeleton& other): Enemy(other)
{
	this->item = other.item->clone();

}

Skeleton::~Skeleton()
{
	delete this->item;
	this->item = nullptr;
 }

bool Skeleton::addItem(const Item* item)
{
	if (!item)
	{
		return false;
	}
	Item* temp = item->clone();

	delete this->item;

	this->item = temp;

	return true;
}

const Item* Skeleton::itemDropped()
{
	std::uniform_int_distribution<> chance(1, 100);
	if (chance(Character::gen) <= this->getCurrentLevel() + BASE_EXP_GIVEN)
	{
		Item* toReturn = this->item;
		this->item = nullptr;
		return toReturn;
	}
	return nullptr;
}


void Skeleton::updateMainStats(int numberOfTimes)
{
	this->setSTR(this->getSTR() + 2 * numberOfTimes);
	this->setINT(this->getINT() + 0 * numberOfTimes);
	this->setAGI(this->getAGI() + 4 * numberOfTimes);

	this->updateMaxHP(this->getMaxHP() + 100 * numberOfTimes);
	this->updateMaxMP(this->getMaxMP() + 0 * numberOfTimes);

	this->setHP(this->getMaxHP());
	this->setMP(this->getMaxMP());
}

CharacterData Skeleton::createSkeletonData(const std::string& name)
{
	CharacterData data;
	data.name = name;

	data.mainStats.STR = 30;
	data.mainStats.INT = 0;
	data.mainStats.AGI = 15;
	data.mainStats.DEF = 5;

	data.maxHP = 500;
	data.maxMP = 0;


	data.mainStats.currentHP = data.maxHP;
	data.mainStats.currentMP = data.maxMP;

	data.currentLevel = 1;
	data.goldCoinsOwned = 0;

	data.statusEffects.clear();

	return data;
}

Enemy* Skeleton::clone()const
{
	return new Skeleton(*this);
}