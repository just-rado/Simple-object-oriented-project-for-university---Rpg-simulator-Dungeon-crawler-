#include "Consumable.h"

Consumable::Consumable(const ItemData& data, int hp_modifier, int mp_modifier, StatusEffectType removeStatusEffect) :
	Item(data , ITEM_TYPE), HP_Modifier(hp_modifier), MP_Modifier(mp_modifier), removeStatusEffect(removeStatusEffect)
{
	
}

Consumable::Consumable(std::ifstream& read, uint64_t ID) : Item(read , ITEM_TYPE , ID)
{
	read.read(reinterpret_cast<char*>(&this->HP_Modifier), sizeof(this->HP_Modifier));

	read.read(reinterpret_cast<char*>(&this->MP_Modifier), sizeof(this->MP_Modifier));

	uint32_t statusEffectValue = 0;
	read.read(reinterpret_cast<char*>(&statusEffectValue), sizeof(statusEffectValue));

	this->removeStatusEffect = static_cast<StatusEffectType>(statusEffectValue);

	if (!read)
	{
		throw std::runtime_error("Could not load consumable data");
	}
}
void Consumable::writeDataToFile(std::ofstream& write)const
{
	Item::writeDataToFile(write);

	write.write(reinterpret_cast<const char*>(&this->HP_Modifier), sizeof(this->HP_Modifier));

	write.write(reinterpret_cast<const char*>(&this->MP_Modifier), sizeof(this->MP_Modifier));

	uint32_t statusEffectValue = static_cast<uint32_t>(this->removeStatusEffect);

	write.write(reinterpret_cast<const char*>(&statusEffectValue), sizeof(statusEffectValue));


	if (!write)
	{
		throw std::runtime_error("Could not load consumable data");
	}
}


Item* Consumable::clone()const
{
	return new Consumable(*this);
}


void Consumable::applyEffectsOfItem(Character* character)const
{
	if (!character)
	{
		return;
	}
	character->setHP(character->getHP() + this->getHPModifier());
	character->setMP(character->getMP() + this->getMPModifier());
	character->removeStatusEffect(this->getStatusEffectToRemove());
}


int Consumable::getHPModifier()const
{
	return this->HP_Modifier;
}
int Consumable::getMPModifier()const
{
	return this->MP_Modifier;
}
StatusEffectType Consumable::getStatusEffectToRemove()const
{
	return this->removeStatusEffect;
}