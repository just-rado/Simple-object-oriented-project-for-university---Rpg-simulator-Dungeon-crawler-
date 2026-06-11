#pragma once
#include "Item.h"
#include "Spell.h"

class Scroll: public Item
{
public:

	Scroll(const ItemData& data, const Spell* spell);
	Scroll(const Scroll& other);
	virtual ~Scroll()override;

	Scroll& operator=(const Scroll& other) = delete;
	virtual Item* clone()const override;


	const Spell* getSpell()const;

private:
	Spell* spell;    

	static constexpr TypeOfItem type = TypeOfItem::SCROLL;
};

