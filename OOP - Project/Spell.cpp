#include "Spell.h"
#include <stdexcept>
Spell::Spell(const std::string& name, const std::string& description ,TypeOfSpell type, AugmentationType damageType , 
	unsigned int manaCost , unsigned int levelRequired)
	:name(name) , description(description) , type(type) , damageType(damageType) , manaCost(manaCost) , levelRequired(levelRequired)
{
	if (name.empty() || description.empty())
	{
		throw std::invalid_argument("Name and description cannot be empty");
	}
	
}

TypeOfSpell Spell::getEffect()const
{
	return this->type;
}
AugmentationType Spell::getType()const
{
	return this->damageType;
}
unsigned int Spell::getManaCost()const
{
	return this->manaCost;
}

unsigned int Spell::getLevelRequired()const
{
	return this->levelRequired;
}
const std::string& Spell::getName()const
{
	return this->name;
}
const std::string& Spell::getDescription()const
{
	return this->description;
}