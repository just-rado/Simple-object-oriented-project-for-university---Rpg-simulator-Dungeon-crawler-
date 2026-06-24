#pragma once
#include "Item.h"
#include "CharacterStats.h"

class Relic: public Item
{
public:

	Relic(const ItemData& data , const CharacterStats& modifiers);

	Relic& operator=(const Relic& other) = delete;

	virtual Item* clone()const override;


	virtual void applyEffectsOfItem(Character* character)const override;
	virtual void removeEffectsOfItem(Character* character)const override;

	CharacterStats getStats()const;



private:
	CharacterStats modifiers;

	static constexpr TypeOfItem ITEM_TYPE = TypeOfItem::RELIC;
};

