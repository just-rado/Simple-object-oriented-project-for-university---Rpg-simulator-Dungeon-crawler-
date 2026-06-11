#pragma once
#include <string>
#include <vector>
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
	TypeOfItem type;
	unsigned int costInGoldCoins;
	float weightInKg;
	unsigned int requiredLevel;
	std::vector<uint64_t> compatibleClasses;
};


class Item
{
public:

	Item(const ItemData& data);

	Item(const Item& other);
	Item& operator=(const Item& other) = delete;

	virtual ~Item() = default;
	virtual Item* clone()const = 0;
	virtual void printInfo()const;

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
	const uint64_t id;
	std::string name;
	Rarity rarity;
	TypeOfItem type;
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

