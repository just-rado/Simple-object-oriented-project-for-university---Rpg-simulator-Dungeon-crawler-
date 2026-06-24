#pragma once
#include <string>
#include <vector>
#include "CharacterStats.h"
#include "Battle.h"
class Information
{
public:

	Information(const Battle& battle , const CharacterStats& stats);


	const Battle& getBattle()const;
	const CharacterStats& getStats()const;

	
private:
	const Battle battle;
	const CharacterStats statsAfterBattle;
};

