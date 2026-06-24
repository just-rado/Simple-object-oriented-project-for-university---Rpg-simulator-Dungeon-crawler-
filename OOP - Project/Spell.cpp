#include "Spell.h"
#include <stdexcept>
#include "StringFunctionsForFiles.h"
Spell::Spell(const std::string& name, const std::string& description ,TypeOfSpell type, AugmentationType damageType , 
	unsigned int manaCost , unsigned int levelRequired)
	:type(type), name(name) , description(description) , damageType(damageType) , manaCost(manaCost) , levelRequired(levelRequired)
{
	if (name.empty() || description.empty())
	{
		throw std::invalid_argument("Name and description cannot be empty");
	}
	
}

Spell::Spell(std::ifstream& read , TypeOfSpell type):type(type) , name(readString(read)) , description(readString(read))
{
	uint32_t damageValue = 0;

	read.read(reinterpret_cast<char*>(&damageValue), sizeof(damageValue));

	if (damageValue > static_cast<uint32_t>(AugmentationType::NONE))
	{
		throw std::runtime_error("Invalid damage type");
	}
		

	this->damageType = static_cast<AugmentationType>(damageValue);

	read.read(reinterpret_cast<char*>(&this->manaCost), sizeof(this->manaCost));
	read.read(reinterpret_cast<char*>(&this->levelRequired), sizeof(this->levelRequired));

	if (!read) 
	{
		throw std::runtime_error("Failed to load Spell from file");
	}

}


void Spell::writeDataToFile(std::ofstream& write)const
{
	
	uint32_t typeValue = static_cast<uint32_t>(this->type);

	write.write(reinterpret_cast<const char*>(&typeValue), sizeof(typeValue));

	writeString(write, this->name);
	writeString(write, this->description);

	
	uint32_t damageValue = static_cast<uint32_t>(this->damageType);

	write.write(reinterpret_cast<const char*>(&damageValue), sizeof(damageValue));

	write.write(reinterpret_cast<const char*>(&this->manaCost), sizeof(this->manaCost));
	write.write(reinterpret_cast<const char*>(&this->levelRequired), sizeof(this->levelRequired));

	if (!write)
	{
		throw std::runtime_error("Failed writing spell");
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