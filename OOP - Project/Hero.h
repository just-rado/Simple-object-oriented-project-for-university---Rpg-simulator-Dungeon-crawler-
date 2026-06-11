#pragma once
#include <vector>
#include "Character.h"
#include "Item.h"
class Hero: public Character
{
public:

	Hero(const CharacterStats& mainStats);
	Hero(const Hero& other);
	Hero& operator=(const Hero& other);
	virtual ~Hero();


private:


	std::vector<Item*> inventory;
	std::vector<Item*> equippedItems;
	// история на промените на характеристиките и битките, в които е участвал.(не знам какво траябва да е това??)

	static constexpr size_t CAPACITY_OF_INVENTORY = 64;
	static constexpr size_t MAX_EQUIPPED_ITEMS = 8;
};

