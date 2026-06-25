#pragma once
#include "Item.h"
#include "Spell.h"

class Scroll: public Item
{
public:

	Scroll(const ItemData& data, const Spell* spell);

	Scroll(std::ifstream& read, uint64_t ID);
	virtual void writeDataToFile(std::ofstream& write)const override;

	Scroll(const Scroll& other);
	virtual ~Scroll()override;

	Scroll& operator=(const Scroll& other) = delete;
	virtual Item* clone()const override;

	virtual void applyEffectsOfItem(Character* character)const override;

	const Spell* getSpell()const;

private:
	Spell* spell;    

	static constexpr TypeOfItem ITEM_TYPE = TypeOfItem::SCROLL;
};

