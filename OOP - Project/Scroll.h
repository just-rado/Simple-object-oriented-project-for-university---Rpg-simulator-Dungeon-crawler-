#pragma once
#include "Item.h"

class Scroll: public Item
{
public:

	Scroll(const ItemData& data, int spell);

	Scroll& operator=(const Scroll& other) = delete;
	virtual Item* clone()const override;


	int getSpell()const;

private:
	int spell; // spell should be a (pointer to ?)object of type Spell   
};

