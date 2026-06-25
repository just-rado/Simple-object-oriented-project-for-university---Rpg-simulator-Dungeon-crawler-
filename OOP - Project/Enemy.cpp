#include "Enemy.h"


uint64_t Enemy::nextID = 1;

Enemy::Enemy(const CharacterData& mainStats, TypeOfEnemy type,  float baseExpGiven): 
	Character(mainStats , TYPE), enemyType(type),  ID(nextID) , weakTo(), baseExperienceGivenIfKilled(baseExpGiven)
{
	++nextID;
}


Enemy::Enemy(std::ifstream& read, TypeOfEnemy enemyType):Character(read) , enemyType(enemyType)
{
	
	read.read(reinterpret_cast<char*>(&this->ID), sizeof(this->ID));
	
	uint32_t size = 0;
	read.read(reinterpret_cast<char*>(&size), sizeof(size));


	if (size > 0)
	{
		this->weakTo.resize(size);

		read.read(reinterpret_cast<char*>(this->weakTo.data()), size * sizeof(AugmentationType));
	}

	read.read(reinterpret_cast<char*>(&this->baseExperienceGivenIfKilled), sizeof(this->baseExperienceGivenIfKilled));

	if (!read)
	{
		throw std::runtime_error("Error");
	}
	

}
void Enemy::writeToFile(std::ofstream& write)const
{
	writeOwnDataToFile(write);
}

void Enemy::writeOwnDataToFile(std::ofstream& write)const
{
	uint32_t enemyTypeValue = static_cast<uint32_t>(this->enemyType);
	write.write(reinterpret_cast<const char*>(&enemyTypeValue), sizeof(enemyTypeValue));

	Character::writeDataToFile(write);

	write.write(reinterpret_cast<const char*>(&this->ID), sizeof(this->ID));

	uint32_t size = static_cast<uint32_t>(this->weakTo.size());
	write.write(reinterpret_cast<const char*>(&size), sizeof(size));

	write.write(reinterpret_cast<const char*>(&this->baseExperienceGivenIfKilled), sizeof(this->baseExperienceGivenIfKilled));

	if (!write)
	{
		throw std::runtime_error("Error");
	}
}

Enemy::Enemy(const Enemy& other): Character(other) 
{
	this->ID = nextID;
	this->enemyType = other.enemyType;
	this->weakTo = other.weakTo;
	this->baseExperienceGivenIfKilled = other.baseExperienceGivenIfKilled;

	++nextID;
}

bool Enemy::addWeakness(AugmentationType weakness)
{
	if (weakness != AugmentationType::NONE)
	{
		this->weakTo.push_back(weakness);
		return true;
	}
	return false;
}

TypeOfEnemy Enemy::getType()const
{
	return this->enemyType;
}

 size_t Enemy::getNumberOfWeaknesses()const
{
	return this->weakTo.size();
}
AugmentationType Enemy::getWeakTo(size_t index)const
{
	return this->weakTo[index];
}
uint64_t Enemy::getID()const
{
	return this->ID;
}

const Item* Enemy::itemDropped()
{
	return nullptr;
}


float Enemy::getBaseExpGainedForKilling()const
{
	return this->baseExperienceGivenIfKilled;
}


bool Enemy::attackHero(Hero* hero)
{
	if (!hero)
	{
		return false;
	}

	int curseMultiplier = 1;
	int blessingMultiplier = 1;
	size_t numberOfStatusEffects = this->getNumberOfStatusEffects();
	for (size_t i = 0; i < numberOfStatusEffects; ++i)
	{
		StatusEffectType type = this->getStatusEffect(i).typeOfEffect;
		if (type == StatusEffectType::CURSE)
		{
			curseMultiplier = 2;
			if (blessingMultiplier > 1)
			{
				break;
			}
		}
		if (type == StatusEffectType::BLESSING)
		{
			blessingMultiplier = 3;
			if (curseMultiplier > 1)
			{
				break;
			}
		}

	}

	std::uniform_int_distribution<> chance(1, 100);
	int missChance = hero->calculateChanceOfMiss() * curseMultiplier;
	if (chance(Character::gen) <= missChance)
	{
		return false;
	}

	int inflictDamage = this->calculateDamage() * blessingMultiplier;

	size_t numberOfEnemyStatusEffects = hero->getNumberOfStatusEffects();
	int protectionMultiplier = 1;
	for (size_t i = 0; i < numberOfEnemyStatusEffects; ++i)
	{
		if (hero->getStatusEffect(i).typeOfEffect == StatusEffectType::PROTECTION)
		{
			protectionMultiplier = 2;
			break;
		}
	}

	unsigned int def = hero->calculateDefence();
	if (def != 0)
	{
		inflictDamage /= (def * protectionMultiplier);
	}


	int newHP = hero->getHP() - inflictDamage;
	hero->setHP(newHP);

	if (hero->getHP() == 0)
	{
		this->setGoldCoins(this->getGoldCoins() + hero->getGoldCoins());
	}

	return true;

}



void Enemy::setNextID(std::ifstream& read)
{
	read.read(reinterpret_cast<char*>(&nextID), sizeof(nextID));
	if (!read)
	{
		throw std::runtime_error("Error");
	}
}
void Enemy::writeNextID(std::ofstream& write)
{
	write.write(reinterpret_cast<const char*>(&nextID), sizeof(nextID));
	if (!write)
	{
		throw std::runtime_error("Error");
	}
}