#include "SpellFactory.h"
#include "HealSpell.h"
#include "DamageSpell.h"
#include "CleanseSpell.h"

Spell* SpellFactory::readSpellFromFile(std::ifstream& is, TypeOfSpell type)
{
	switch (type)
	{
	case TypeOfSpell::DAMAGE:
		return new (std::nothrow)DamageSpell(is);
	case TypeOfSpell::HEAL:
		return new (std::nothrow)HealSpell(is);
	case TypeOfSpell::CLEANSE:
		return new (std::nothrow)CleanseSpell(is);
	default:
		return nullptr;
	}
}