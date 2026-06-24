#pragma once
#include <string>
#include <vector>
#include "Classes.h"
#include "Character.h"
#include <fstream>
enum class Rarity
{
	COMMON,
	RARE,
	EPIC,
	LEGENDARY,
};
enum class TypeOfItem
{
	WEAPON,
	ARMOR,
	CONSUMABLE,
	SCROLL,
	RELIC,
};

struct ItemData
{
	std::string name;
	Rarity rarity;
	unsigned int costInGoldCoins;
	float weightInKg;
	unsigned int requiredLevel;
	std::vector<uint64_t> compatibleClasses;
};


class Item
{
public:

	Item(const ItemData& data , TypeOfItem type);

	Item(std::ifstream& read , TypeOfItem type , uint64_t ID);
	virtual void writeDataToFile(std::ofstream& write)const;
	
	Item(const Item& other);
	Item& operator=(const Item& other) = delete;

	virtual ~Item() = default;
	virtual Item* clone()const = 0;
	virtual void printInfo()const;
	virtual void applyEffectsOfItem(Character* character)const;
	virtual void removeEffectsOfItem(Character* character)const;
	virtual AugmentationType getAugmentationType()const;

	bool checkIfClassIsCompatible(HeroClass classOfHero)const;

	uint64_t getId()const;
	const std::string& getName()const;
	Rarity getRarity()const;
	float getWeight()const;
	unsigned int getCost()const;
	TypeOfItem getTypeOfItem()const;
	unsigned int getRequiredLevel()const;
	const std::vector<uint64_t>& getCompatibleClasses()const;

protected:
	void setTypeOfItem(TypeOfItem type);


private:
	TypeOfItem type;
	const uint64_t id;
	const std::string name;
	Rarity rarity;
	unsigned int costInGoldCoins;
	float weightInKg;
	unsigned int requiredLevel;
	std::vector<uint64_t> compatibleClasses; // bitmask

	static uint64_t nextId;
	constexpr static int CLASSES_PER_UINT64 = 64;

	
	size_t optimalSizeOfVector()const;
	void printRarity()const;
	void printCompatibleClasses()const;

	

};

