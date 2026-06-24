#include "CleanseSpell.h"
#include <stdexcept>

CleanseSpell::CleanseSpell(const std::string& name, const std::string& description ,AugmentationType damageType,
	unsigned int manaCost , unsigned int levelRequired ,StatusEffectType statusEffect):
	Spell(name, description ,TYPE, damageType , manaCost , levelRequired), removeStatusEffect(statusEffect)
{
	if (statusEffect == StatusEffectType::NONE)
	{
		throw std::invalid_argument("Invalid");
	}
}

CleanseSpell::CleanseSpell(std::ifstream& read)  : Spell(read , TYPE)
{
	uint32_t statusEffectValue = 0;

	read.read(reinterpret_cast<char*>(&statusEffectValue), sizeof(statusEffectValue));

	this->removeStatusEffect = static_cast<StatusEffectType>(statusEffectValue);

	if (!read)
	{
		throw std::runtime_error("Failed to load cleanse spell from file");
	}
}

void CleanseSpell::writeDataToFile(std::ofstream& write)const
{
	Spell::writeDataToFile(write);

	uint32_t statusEffectValue = static_cast<uint32_t>(this->removeStatusEffect);
	write.write(reinterpret_cast<const char*>(&statusEffectValue), sizeof(statusEffectValue));

	if (!write)
	{
		throw std::runtime_error("Failed writing cleanse spell");
	}

}

Spell* CleanseSpell::clone()const
{
	return new (std::nothrow)CleanseSpell(*this);
}

StatusEffectType CleanseSpell::getStatusEffect()const
{
	return this->removeStatusEffect;
}

bool CleanseSpell::applyEffectOfSpell(Character* character)const
{	
	if (!character)
	{
		return false;
	}
	character->removeStatusEffect(this->removeStatusEffect);
	return true;
}