#include "ItemFactory.h"
#include "Armor.h"
#include "Scroll.h"
#include "Relic.h"
#include "Weapon.h"
#include "Consumable.h"

Item* ItemFactory::loadItemFromFile(std::ifstream& is, TypeOfItem type , uint64_t ID)
{

	switch (type)
	{
	case TypeOfItem::WEAPON:
		return new Weapon(is, ID);
	case TypeOfItem::ARMOR:
		return new Armor(is, ID);
	case TypeOfItem::CONSUMABLE:
		return new Consumable(is, ID);
	case TypeOfItem::SCROLL:
		return new Scroll(is, ID);
	case TypeOfItem::RELIC:
		return new Relic(is, ID);
	default:
		return nullptr;
	}
}