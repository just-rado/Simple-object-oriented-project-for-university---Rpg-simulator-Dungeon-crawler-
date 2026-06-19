#include "Spell.h"
#include <stdexcept>
Spell::Spell(const std::string& name, const std::string& description ,TypeOfSpell type, AgmentationType damageType , unsigned int manaCost)
	:name(name) , description(description) , type(type) , damageType(damageType) , manaCost(manaCost)
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
AgmentationType Spell::getType()const
{
	return this->damageType;
}
unsigned int Spell::getManaCost()const
{
	return this->manaCost;
}

const std::string& Spell::getName()const
{
	return this->name;
}
const std::string& Spell::getDescription()const
{
	return this->description;
}