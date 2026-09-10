#pragma once
#include "Spell.h"
#include <fstream>
class SpellFactory
{
public:
	static Spell* readSpellFromFile(std::ifstream& is, TypeOfSpell type);
};

