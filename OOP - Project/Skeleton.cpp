#include "Skeleton.h"
#include <random>
Skeleton::Skeleton(const std::string& name): Enemy(createSkeletonData(name) , ENEMY_TYPE , BASE_EXP_GIVEN) , item(nullptr)
{

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