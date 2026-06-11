#include "Scroll.h"

Scroll::Scroll(const ItemData& data, const Spell* spell): Item(data)
{
	this->spell = spell->clone();

	setTypeOfItem(type);
}
Scroll::Scroll(const Scroll& other): Item(other)
{
	this->spell = other.spell->clone();
}
Scroll::~Scroll()
{
	delete this->spell;
	this->spell = nullptr;
}


Item* Scroll::clone()const
{
	return new Scroll(*this);
}

const Spell* Scroll::getSpell()const
{
	return this->spell;
}