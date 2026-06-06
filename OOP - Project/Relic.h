#pragma once
#include "Item.h"

class Relic: public Item
{
public:

	Relic(const ItemData& data);

	Relic& operator=(const Relic& other) = delete;

	virtual Item* clone()const override;



private:
	// think what member variables should relic have

};

