#include "Hero.h"
#include <stdexcept>
#include "Armor.h"
#include "Relic.h"
#include "Weapon.h"
#include "Consumable.h"


Hero::Hero(const CharacterData& mainStats , HeroClass heroClass): Character(mainStats , TYPE) , heroClass(heroClass) ,
			inventory() , equippedItems() , history()
{

}
Hero::Hero(const Hero& other): Character(other)
{
	this->history = other.history;
	handleHeapMemory(other.inventory, other.equippedItems);	
	this->heroClass = other.heroClass;
	
}
Hero& Hero::operator=(const Hero& other)
{
	if (this != &other)
	{
		std::vector<Information> temp(other.history);

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
		std::swap(this->history, temp);
	}
	return *this;
}
Hero::~Hero()
{
	deleteHeapMemory(this->inventory , CAPACITY_OF_INVENTORY);
	deleteHeapMemory(this->equippedItems , MAX_EQUIPPED_ITEMS);
}


bool Hero::addInformation(const Battle& battle, const CharacterStats& stats)
{
	this->history.emplace_back(battle, stats);
}


bool Hero::collectItem(Item*& item)
{
	if (!item)
	{
		return false;
	}
	for (size_t i = 0; i < CAPACITY_OF_INVENTORY; ++i)
	{
		if (!this->inventory[i])
		{
			if(item->getTypeOfItem() == TypeOfItem::RELIC)
			{
				item->applyEffectsOfItem(this);

			}
			std::swap(item, this->inventory[i]); 
			return true;
		}
		
	}
	return false;
}

Item* Hero::dropItemFromInventory(uint64_t ID)
{
	for(size_t i = 0; i < CAPACITY_OF_INVENTORY; ++i)
	{
		if (this->inventory[i] && this->inventory[i]->getId() == ID)
		{
			if (this->inventory[i]->getTypeOfItem() == TypeOfItem::RELIC)
			{
				this->inventory[i]->removeEffectsOfItem(this);
			}
			Item* item = this->inventory[i]; 
			this->inventory[i] = nullptr;
			return item;
		}
	}
	return nullptr;
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
	
		if (typeOfItem != TypeOfItem::RELIC && typeOfItem != TypeOfItem::CONSUMABLE && typeOfItem != TypeOfItem::SCROLL)
		{
			if (this->equippedItems[slot])
			{
				this->equippedItems[slot]->removeEffectsOfItem(this);
			}
			this->inventory[i]->applyEffectsOfItem(this);
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
			if (this->equippedItems[slot]->getTypeOfItem() != TypeOfItem::RELIC)
			{
				this->equippedItems[slot]->removeEffectsOfItem(this);
			}

			std::swap(this->equippedItems[slot], this->inventory[i]);
			return true;
		}
	}
	return false;
	
}


bool Hero::usePotion(Consumable* potion)
{
	if (!potion)
	{
		return false;
	}
			
	potion->applyEffectsOfItem(this);
			
	return true;	
}

bool Hero::useScroll(Character* character , Scroll* scroll)
{
	if (!character || !scroll)
	{
		return false;
	}

	scroll->getSpell()->applyEffectOfSpell(character);

	return true;
}

unsigned int Hero::calculateDamage()const
{
	size_t slot = this->getItemSlotFor(TypeOfItem::WEAPON);
	int damage = this->getSTR() * Character::STR_TO_ATTACK_DMG_MULTIPLIER;
	if(this->equippedItems[slot])
	{
		std::uniform_int_distribution<> chance(1, 100);

		int amplifier = 1;
		Weapon* weapon = static_cast<Weapon*>(this->equippedItems[slot]);
		if (chance(Character::gen) <= weapon->getCriticalChance())
		{
			amplifier = 3;
		}
		damage += weapon->getDmgValue() * amplifier;
	}
	return damage;
}
unsigned int Hero::calculateDefence()const
{
	size_t slot = this->getItemSlotFor(TypeOfItem::ARMOR);
	int defence = this->getDEF();
	if (this->equippedItems[slot])
	{
		Armor* armor = static_cast<Armor*>(this->equippedItems[slot]);
		defence *= armor->getProtectionValue();
	}
	return defence;
}

bool Hero::attackEnemy(Enemy* enemy)
{
	if (!enemy)
	{
		return false;
	}

	int curseMultiplier = 1;
	int blessingMultiplier = 1;
	size_t numberOfStatusEffects = this->getNumberOfStatusEffects();
	for (size_t i = 0; i < numberOfStatusEffects; ++i)
	{
		StatusEffectType type = this->getStatusEffect(i).typeOfEffect;
		if (type == StatusEffectType::CURSE)
		{
			curseMultiplier = 3;
			if (blessingMultiplier > 1)
			{
				break;
			}
		}
		if (type == StatusEffectType::BLESSING)
		{
			blessingMultiplier = 2;
			if (curseMultiplier > 1)
			{
				break;
			}
		}

	}

	std::uniform_int_distribution<> chance(1, 100);
	int missChance = enemy->calculateChanceOfMiss() * curseMultiplier;
	if (chance(Character::gen) <= missChance)
	{
		return false;
	}

	int inflictDamage = this->calculateDamage() * blessingMultiplier;

	size_t numberOfEnemyStatusEffects = enemy->getNumberOfStatusEffects();
	int protectionMultiplier = 1;
	for (size_t i = 0; i < numberOfEnemyStatusEffects; ++i)
	{
		if (enemy->getStatusEffect(i).typeOfEffect == StatusEffectType::PROTECTION)
		{
			protectionMultiplier = 2;
			break;
		}
	}

	size_t slot = getItemSlotFor(TypeOfItem::WEAPON);
	int weaknessMultiplier = 1;
	if (this->equippedItems[slot])
	{
		size_t numberOfEnemyWeaknesses = enemy->getNumberOfWeaknesses();
		AugmentationType augment = (this->equippedItems[slot]->getAugmentationType());

		for (size_t i = 0; i < numberOfEnemyWeaknesses; ++i)
		{
			if (enemy->getWeakTo(i) == augment)
			{
				weaknessMultiplier = 2;
				break;
			}
		}
	}
	inflictDamage *= weaknessMultiplier;
	
	unsigned int def = enemy->calculateDefence();
	if (def != 0)
	{
		inflictDamage /= (def * protectionMultiplier);
	}


	int newHP = enemy->getHP() - inflictDamage;
	enemy->setHP(newHP);
	if (enemy->getHP() == 0)
	{
		this->setGoldCoins(this->getGoldCoins() + enemy->getGoldCoins());
		int differenceInLevelMultiplier = 1;

		int heroLevel = this->getCurrentLevel();
		int enemyLevel = enemy->getCurrentLevel();

		if (heroLevel < enemyLevel)
		{
			differenceInLevelMultiplier = (enemyLevel - heroLevel);
		}
		this->setLevel(this->getCurrentLevel() + differenceInLevelMultiplier * enemy->getBaseExpGainedForKilling());

	}
	return true;

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
	size_t inventoryIndexBeforeFail = 0;
	size_t eqippedItemIndexBeforeFail = 0;

	try
	{
		for (size_t i = 0; i < Hero::CAPACITY_OF_INVENTORY; ++i)
		{
			++inventoryIndexBeforeFail;
			if (inventory[i])
			{
				this->inventory[i] = inventory[i]->clone();
				
			}
		}

		for (size_t i = 0; i < Hero::MAX_EQUIPPED_ITEMS; ++i)
		{
			++eqippedItemIndexBeforeFail;
			if (equippedItems[i])
			{
				this->equippedItems[i] = equippedItems[i]->clone();
			}
			
		}
		
	}
	catch(...)
	{
		deleteHeapMemory(this->inventory, inventoryIndexBeforeFail);
		deleteHeapMemory(this->equippedItems , eqippedItemIndexBeforeFail);
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
	for (size_t i = 0; i < CAPACITY_OF_INVENTORY; ++i)
	{
		std::swap(this->inventory[i], other.inventory[i]);
	}
	std::swap(this->history, other.history);
	for (size_t i = 0; i < MAX_EQUIPPED_ITEMS; ++i)
	{
		std::swap(this->equippedItems[i], other.equippedItems[i]);
	}
	std::swap(this->history, other.history);
}

