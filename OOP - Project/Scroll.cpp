#include "Scroll.h"
#include "DamageSpell.h"
#include "HealSpell.h"
#include "CleanseSpell.h"
#include "SpellFactory.h"

Scroll::Scroll(const ItemData& data, const Spell* spell): Item(data , ITEM_TYPE)
{
	if (!spell)
	{
		throw std::invalid_argument("Error");
	}
	this->spell = spell->clone();

}

Scroll::Scroll(std::ifstream& read, uint64_t ID) : Item(read , ITEM_TYPE , ID)
{
	bool hasSpell = false;

	read.read(reinterpret_cast<char*>(&hasSpell), sizeof(hasSpell));
	if (!read)
	{
		throw std::runtime_error("Error");
	}

	if (!hasSpell)
	{
		this->spell = nullptr;
		return;
	}

	uint32_t typeOfSpellValue = 0;
	read.read(reinterpret_cast<char*>(&typeOfSpellValue), sizeof(typeOfSpellValue));
	if (!read)
	{
		throw std::runtime_error("Error");
	}
	TypeOfSpell type = static_cast<TypeOfSpell>(typeOfSpellValue);
	
	
	SpellFactory factory;
	this->spell = factory.readSpellFromFile(read, type);
	
	if (!read || !this->spell)
	{
		delete this->spell;
		throw std::runtime_error("Error");
	}


}
void Scroll::writeDataToFile(std::ofstream& write)const
{
	Item::writeDataToFile(write);

	bool hasSpell = false;
	if (this->spell)
	{
		hasSpell = true;
	}

	write.write(reinterpret_cast<const char*>(&hasSpell), sizeof(hasSpell));
	if (!write)
	{
		throw std::runtime_error("Error");
	}

	if (!hasSpell)
	{
		return;
	}

	this->spell->writeDataToFile(write);


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

void Scroll::applyEffectsOfItem(Character* character)const
{
	if (!character)
	{
		return;
	}
	this->getSpell()->applyEffectOfSpell(character);
}

const Spell* Scroll::getSpell()const
{
	return this->spell;
}