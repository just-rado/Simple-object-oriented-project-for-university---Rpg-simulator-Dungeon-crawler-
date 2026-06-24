#include "DamageSpell.h"
#include <stdexcept>
#include "Enemy.h"
DamageSpell::DamageSpell(const std::string& name, const std::string& description ,AugmentationType damageType ,unsigned int manaCost,  
	unsigned int levelRequired ,int dmgValue):
	Spell(name , description , TYPE , damageType , manaCost , levelRequired) , damageValue(dmgValue)
{
	if (dmgValue < 0)
	{
		throw std::invalid_argument("Invalid");
	}
}

DamageSpell::DamageSpell(std::ifstream& read) : Spell(read , TYPE)
{
	read.read(reinterpret_cast<char*>(&this->damageValue), sizeof(this->damageValue));
	if (!read)
	{
		throw std::runtime_error("Failed to load damage spell from file");
	}
}

void DamageSpell::writeDataToFile(std::ofstream& write)const
{
	Spell::writeDataToFile(write);

	write.write(reinterpret_cast<const char*>(&this->damageValue), sizeof(this->damageValue));

	if (!write)
	{
		throw std::runtime_error("Failed writing damage spell");
	}
 }


Spell* DamageSpell::clone()const
{
	return new (std::nothrow) DamageSpell(*this);
 }
int DamageSpell::getDamageValue()const
{
	return this->damageValue;
}

bool DamageSpell::applyEffectOfSpell(Character* character)const
{
	if (!character)
	{
		return false;
	}
	Enemy* isEnemy = dynamic_cast<Enemy*>(character);
	if (!isEnemy)
	{
		character->setHP(character->getHP() - this->damageValue);
		return true;
	}

	AugmentationType augment = this->getType();
	size_t numberOfWeaknesses = isEnemy->getNumberOfWeaknesses();
	size_t amplifyDmg = 1;
	for (size_t i = 0; i < numberOfWeaknesses; ++i)
	{
		if (augment == isEnemy->getWeakTo(i))
		{
			amplifyDmg = 2;
			break;
		}
	}
	
	character->setHP(character->getHP() - this->damageValue * amplifyDmg);
	return true;
}