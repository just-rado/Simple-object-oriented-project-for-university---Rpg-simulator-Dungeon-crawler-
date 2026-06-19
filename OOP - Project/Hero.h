#pragma once
#include "CharacterStats.h"
#include "Character.h"
#include "Item.h"
#include "Battle.h"
#include "Enemy.h"
#include "Classes.h"
class Hero: public Character
{
public:

	Hero(const CharacterData& mainStats , HeroClass heroClass);
	Hero(const Hero& other);
	Hero& operator=(const Hero& other);
	virtual ~Hero();

	virtual void equipItem(uint64_t itemID);
	void unequipItem(size_t slot);

	virtual void attackEnemy(const Enemy* enemy) = 0;

	virtual Hero* clone()const = 0;

protected:
	static constexpr unsigned int STR_TO_HEALTH_MULTIPLIER = 10;
	static constexpr unsigned int INT_TO_MANA_MULTIPLIER = 2;
	static constexpr unsigned int AGI_TO_DEF_MULTIPLIER = 1;

	static size_t getItemSlotFor(TypeOfItem type);
	void swap(Hero& hero)noexcept;
private:
	class Information
	{
	public:
		Information();
		Information(const Information& other) = delete;
		Information& operator=(const Information& other) = delete;
		~Information();

		bool addBattle(const std::string& nameOfRoom, const std::vector<std::string>& namesOfHeroes, const std::vector<uint64_t>& IDsOfEnemies);
		void addStatsAfterBattle(const CharacterStats& stats);

	private:
		Battle* battle;
		CharacterStats statsAfterBattle;
	};

	static constexpr size_t CAPACITY_OF_INVENTORY = 64;
	static constexpr size_t MAX_EQUIPPED_ITEMS = 4;
	

	HeroClass heroClass;
	Item* inventory[CAPACITY_OF_INVENTORY];
	Item* equippedItems[MAX_EQUIPPED_ITEMS];
	std::vector<Information> history;

	
	
	void handleHeapMemory(const Item* const (&inventory)[CAPACITY_OF_INVENTORY], const Item* const (&equippedItems)[MAX_EQUIPPED_ITEMS]);
	static void deleteHeapMemory(Item* vector[] , size_t size);

	static void copyPointers(Item* lhs[], Item* rhs[], size_t size);

	
};

