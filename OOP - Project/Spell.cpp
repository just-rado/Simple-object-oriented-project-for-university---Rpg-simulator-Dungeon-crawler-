#include "Spell.h"
#include <stdexcept>
Spell::Spell(const std::string& name, const std::string& description ,TypeOfSpell type, DamageType damageType)
	:name(name) , description(description) , type(type) , damageType(damageType)
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
DamageType Spell::getType()const
{
	return this->damageType;
}


const std::string& Spell::getName()const
{
	return this->name;
}
const std::string& Spell::getDescription()const
{
	return this->description;
}