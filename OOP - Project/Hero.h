#pragma once
#include <vector>
#include "CharacterStats.h"
#include "Character.h"
#include "Item.h"
#include "Battle.h"

class Hero: public Character
{
public:

	Hero(const CharacterData& mainStats);
	Hero(const Hero& other);
	Hero& operator=(const Hero& other);
	virtual ~Hero();

	virtual Hero* clone()const = 0;


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


	std::vector<Item*> inventory;
	std::vector<Item*> equippedItems;
	std::vector<Information> history;

	static constexpr size_t CAPACITY_OF_INVENTORY = 64;
	static constexpr size_t MAX_EQUIPPED_ITEMS = 8;

	void handleHeapMemory(std::vector<Item*> inventory, std::vector<Item*> equippedItems);
	void deleteHeapMemory(std::vector<Item*> vector);
};

