#include "HealSpell.h"

HealSpell::HealSpell(const std::string& name, const std::string& description ,AugmentationType damageType,unsigned int manaCost , 
	unsigned int levelRequired ,unsigned int healValue):
	Spell(name, description , TYPE , damageType , manaCost , levelRequired) , healValue(healValue)
{
	
}

HealSpell::HealSpell(std::ifstream& read): Spell(read , TYPE)
{
	read.read(reinterpret_cast<char*>(&this->healValue), sizeof(this->healValue));

	if (!read)
	{
		throw std::runtime_error("Failed to load heal spell from file");
	}
}

void HealSpell::writeDataToFile(std::ofstream& write)const
{
	Spell::writeDataToFile(write);

	write.write(reinterpret_cast<const char*>(&this->healValue), sizeof(this->healValue));

	if (!write)
	{
		throw std::runtime_error("Failed writing heal spell");
	}

}

Spell* HealSpell::clone()const
{
	return new (std::nothrow)HealSpell(*this);
}
unsigned int HealSpell::getHealValue()const
{
	return this->healValue;
}

bool HealSpell::applyEffectOfSpell(Character* character)const
{
	if (!character)
	{
		return false;
	}
	character->setHP(character->getHP() + this->healValue);
	return true;
}