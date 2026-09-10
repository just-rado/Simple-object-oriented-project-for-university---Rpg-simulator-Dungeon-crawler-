#include "SpellFactory.h"
#include "HealSpell.h"
#include "DamageSpell.h"
#include "CleanseSpell.h"

Spell* SpellFactory::readSpellFromFile(std::ifstream& is, TypeOfSpell type)
{
	switch (type)
	{
	case TypeOfSpell::DAMAGE:
		return new DamageSpell(is);
	case TypeOfSpell::HEAL:
		return new HealSpell(is);
	case TypeOfSpell::CLEANSE:
		return new CleanseSpell(is);
	default:
		return nullptr;
	}
}