#pragma once
#include "CharacterStats.h"
#include "Character.h"
#include "Item.h"
#include "Battle.h"
#include "Enemy.h"
#include "Classes.h"
#include "Scroll.h"
#include "Consumable.h"
#include "Information.h"
#include <random>
class Enemy;

class Hero: public Character
{
public:

	Hero(const CharacterData& mainStats , HeroClass heroClass);
	Hero(const Hero& other);
	Hero& operator=(const Hero& other);
	virtual ~Hero()override;

	bool equipItem(uint64_t itemID);
	bool unequipItem(size_t slot);

	const Item* getItemFromInvetoryAtIndex(size_t index)const;
	const Item* getItemFromEquippedItems(TypeOfItem type)const;

	bool collectItem(Item*& item);
	Item* dropItemFromInventory(uint64_t itemID);
	
	bool usePotion(Consumable* consumable);
	bool useScroll(Character* character , Scroll* scroll);
	
	bool addInformation(const Battle& battle, const CharacterStats& stats);

	virtual bool useAbility(size_t ability , Character* character = nullptr) = 0;
	virtual size_t getNumberOfAbilites()const = 0;
	virtual void printAbilities()const = 0;
	virtual bool requiresATarget(size_t ability)const = 0;
	virtual Hero* clone()const override = 0;
	virtual bool attackEnemy(Enemy* enemy);


	virtual unsigned int calculateDamage()const override;
	virtual unsigned int calculateDefence()const override;

protected:
	virtual void updateMainStats(int numberOfTimes)override = 0;
	static size_t getItemSlotFor(TypeOfItem type);


	void swap(Hero& hero)noexcept;
private:

	static constexpr size_t CAPACITY_OF_INVENTORY = 64;
	static constexpr size_t MAX_EQUIPPED_ITEMS = 4;
	
	HeroClass heroClass;
	Item* inventory[CAPACITY_OF_INVENTORY];
	Item* equippedItems[MAX_EQUIPPED_ITEMS];
	std::vector<Information> history;

	
	void handleHeapMemory(Item* const (&inventory)[CAPACITY_OF_INVENTORY], Item* const  (&equippedItems)[MAX_EQUIPPED_ITEMS]);
	static void deleteHeapMemory(Item* vector[] , size_t size);

	static void copyPointers(Item* lhs[], Item* rhs[], size_t size);


	static constexpr TypeOfCharacter TYPE = TypeOfCharacter::HERO;
	
};

