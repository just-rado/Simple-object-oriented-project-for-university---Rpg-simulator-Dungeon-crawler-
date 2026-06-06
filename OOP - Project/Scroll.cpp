#include "Scroll.h"


Scroll::Scroll(const ItemData& data, int spell) : Item(data) , spell(spell)
{
	// maybe add logic for spell
}

Item* Scroll::clone()const
{
	return new Scroll(*this);
}


int Scroll::getSpell()const
{
	return this->spell; // remake return type
}