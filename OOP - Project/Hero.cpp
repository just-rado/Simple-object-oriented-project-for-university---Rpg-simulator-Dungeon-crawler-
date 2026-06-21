#include "Hero.h"
#include <stdexcept>
#include "Armor.h"
#include "Relic.h"
Hero::Information::Information()
{
	this->battle = nullptr;
	this->statsAfterBattle = CharacterStats();
}

bool Hero::Information::addBattle(const std::string& nameOfRoom, const std::vector<std::string>& namesOfHeroes, 
							const std::vector<uint64_t>& IDsOfEnemies)
{

	this->battle = new (std::nothrow) Battle(nameOfRoom, namesOfHeroes, IDsOfEnemies);
	if (!this->battle)
	{
		return false;
	}
	return true;
}
void Hero::Information::addStatsAfterBattle(const CharacterStats& stats)
{
	this->statsAfterBattle = stats;
}

Hero::Information::~Information()
{
	delete this->battle;
	this->battle = nullptr;
}



Hero::Hero(const CharacterData& mainStats , HeroClass heroClass): Character(mainStats) , heroClass(heroClass) ,
			inventory() , equippedItems() , history()
{

}
Hero::Hero(const Hero& other): Character(other)
{
	handleHeapMemory(other.inventory, other.equippedItems);	
	this->heroClass = other.heroClass;
}
Hero& Hero::operator=(const Hero& other)
{
	if (this != &other)
	{
		Item* toDeleteInventory[CAPACITY_OF_INVENTORY]{};
		copyPointers(toDeleteInventory , this->inventory, CAPACITY_OF_INVENTORY);

		Item* toDeleteEquippedItems[MAX_EQUIPPED_ITEMS]{};
		copyPointers(toDeleteEquippedItems , this->equippedItems, MAX_EQUIPPED_ITEMS);
		
		try
		{
			handleHeapMemory(other.inventory, other.equippedItems);
		}
		catch (...)
		{
			copyPointers(this->inventory, toDeleteInventory, CAPACITY_OF_INVENTORY);
			copyPointers(this->equippedItems, toDeleteEquippedItems, MAX_EQUIPPED_ITEMS);
			throw;
		}
		
		try
		{
			Character::operator=(other);
		}
		catch(...)
		{
			deleteHeapMemory(this->inventory , CAPACITY_OF_INVENTORY);
			copyPointers(this->inventory, toDeleteInventory, CAPACITY_OF_INVENTORY);

			deleteHeapMemory(this->equippedItems , MAX_EQUIPPED_ITEMS);
			copyPointers(this->equippedItems, toDeleteEquippedItems, MAX_EQUIPPED_ITEMS);
			
			throw;
		}
		deleteHeapMemory(toDeleteInventory , CAPACITY_OF_INVENTORY);
		deleteHeapMemory(toDeleteEquippedItems, MAX_EQUIPPED_ITEMS);
		this->heroClass = other.heroClass;
	}
	return *this;
}
Hero::~Hero()
{
	deleteHeapMemory(this->inventory , CAPACITY_OF_INVENTORY);
	deleteHeapMemory(this->equippedItems , MAX_EQUIPPED_ITEMS);
}


bool Hero::equipItem(uint64_t itemID)
{
	for (size_t i = 0; i < CAPACITY_OF_INVENTORY; ++i)
	{
		if (!inventory[i] || this->inventory[i]->getId() != itemID)
		{
			continue;
		}

		if (!this->inventory[i]->checkIfClassIsCompatible(this->heroClass) || this->getCurrentLevel() < this->inventory[i]->getRequiredLevel())
		{
			return false;
		}

		TypeOfItem typeOfItem = this->inventory[i]->getTypeOfItem();
		size_t slot = getItemSlotFor(typeOfItem);
	
		if (typeOfItem == TypeOfItem::ARMOR)
		{
			if (this->equippedItems[slot])
			{
				Armor* toUneqiupArmor = static_cast<Armor*>(this->equippedItems[slot]);
				removeCharacterStatsModifiers(toUneqiupArmor->getModifiers());
			}
			Armor* toEquipArmor = static_cast<Armor*>(this->inventory[i]);
			addCharacterStatsModifiers(toEquipArmor->getModifiers());
		}

		std::swap(this->inventory[i], this->equippedItems[slot]);
		break;
		
	}
	return true;
}

bool Hero::unequipItem(size_t slot)
{
	if (slot >= MAX_EQUIPPED_ITEMS || !this->equippedItems[slot])
	{
		return false;
	}

	for (size_t i = 0; i < CAPACITY_OF_INVENTORY; ++i)
	{
		if (!this->inventory[i])
		{
			if (this->equippedItems[slot]->getTypeOfItem() == TypeOfItem::ARMOR)
			{
				Armor* toUnequip = static_cast<Armor*>(this->equippedItems[slot]);
				removeCharacterStatsModifiers(toUnequip->getModifiers());
			}

			std::swap(this->equippedItems[slot], this->inventory[i]);
			return true;
		}
	}
	return false;
	
}

const Item* Hero::getItemFromInvetoryAtIndex(size_t index)const
{
	if (index < CAPACITY_OF_INVENTORY)
	{
		return this->inventory[index];
	}
	return nullptr;
}
const Item* Hero::getItemFromEquippedItems(TypeOfItem type)const
{
	return this->equippedItems[getItemSlotFor(type)];
}



size_t Hero::getItemSlotFor(TypeOfItem type)
{
	switch (type)
	{
	case TypeOfItem::WEAPON: return 0;
		
	case TypeOfItem::ARMOR: return 1;

	case TypeOfItem::RELIC: return 2;

	default: return 3;
	}

}

void Hero::handleHeapMemory(Item* const (&inventory)[CAPACITY_OF_INVENTORY],  Item* const  (&equippedItems)[MAX_EQUIPPED_ITEMS])
{
	size_t inventorySlotIndex = 0;
	size_t eqippedItemSlotIndex = 0;
	try
	{
		for (size_t i = 0; i < Hero::CAPACITY_OF_INVENTORY; ++i)
		{
			++inventorySlotIndex;
			if (inventory[i])
			{
				this->inventory[i] = inventory[i]->clone();
				
			}
		}

		for (size_t i = 0; i < Hero::MAX_EQUIPPED_ITEMS; ++i)
		{
			++eqippedItemSlotIndex;
			if (equippedItems[i])
			{
				this->equippedItems[i] = equippedItems[i]->clone();
			}
			
		}
		
	}
	catch(...)
	{
		deleteHeapMemory(this->inventory, inventorySlotIndex);
		deleteHeapMemory(this->equippedItems , eqippedItemSlotIndex);
		throw;
	}
	
}
void Hero::deleteHeapMemory(Item* vector[], size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		delete vector[i];
		vector[i] = nullptr;
	}

}


void Hero::copyPointers(Item* lhs[], Item* rhs[], size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		lhs[i] = rhs[i];
	}
}

void Hero::swap(Hero& other)noexcept
{
	Character::swap(other);
	std::swap(this->heroClass, other.heroClass);
	std::swap(this->inventory, other.inventory);
	std::swap(this->history, other.history);
	std::swap(this->equippedItems, other.equippedItems);

}

