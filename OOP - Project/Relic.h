#pragma once
#include "Item.h"
#include "CharacterStats.h"

class Relic: public Item
{
public:

	Relic(const ItemData& data , const CharacterStats& modifiers);

	Relic& operator=(const Relic& other) = delete;

	virtual Item* clone()const override;



private:
	CharacterStats modifiers;
};

