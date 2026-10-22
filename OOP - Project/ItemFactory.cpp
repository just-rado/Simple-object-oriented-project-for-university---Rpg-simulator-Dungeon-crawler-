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
		return new (std::nothrow)Weapon(is, ID);
	case TypeOfItem::ARMOR:
		return new (std::nothrow)Armor(is, ID);
	case TypeOfItem::CONSUMABLE:
		return new (std::nothrow)Consumable(is, ID);
	case TypeOfItem::SCROLL:
		return new (std::nothrow)Scroll(is, ID);
	case TypeOfItem::RELIC:
		return new (std::nothrow)Relic(is, ID);
	default:
		return nullptr;
	}
}