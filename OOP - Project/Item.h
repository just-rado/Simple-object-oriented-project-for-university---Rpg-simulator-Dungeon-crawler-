#pragma once
#include <string>
#include <vector>
enum class Rarity
{
	COMMON,
	RARE,
	EPIC,
	LEGENDARY
};


class Item
{
public:

	Item(const std::string& name, Rarity rarity, float cost, float weightInKg,
		unsigned int requiredLevel, const std::vector<uint64_t>& compatibleClasses);

	Item(const Item& other);
	Item& operator=(const Item& other) = delete;

	virtual ~Item() = default;
	virtual Item* clone()const = 0;
	virtual void printInfo()const;

	uint64_t getId()const;
	const std::string& getName()const;
	Rarity getRarity()const;
	unsigned int getRequiredLevel()const;
	const std::vector<uint64_t>& getCompatibleClasses()const;

private:
	const uint64_t id;
	std::string name;
	Rarity rarity;
	float cost;
	float weightInKg;
	unsigned int requiredLevel;
	std::vector<uint64_t> compatibleClasses; // bitmask

	static uint64_t nextId;
	constexpr static int MAX_AMOUNT_OF_ClASSES_STORED_INSIDE_UINT64 = 64;

	size_t optimalSizeOfVector();
	void printRarity()const;
	void printCompatibleClasses()const;


};

