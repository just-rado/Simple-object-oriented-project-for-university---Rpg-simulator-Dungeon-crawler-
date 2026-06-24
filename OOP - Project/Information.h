#pragma once
#include <string>
#include <vector>
#include "CharacterStats.h"
#include "Battle.h"
#include <fstream>
class Information
{
public:

	Information(const Battle& battle , const CharacterStats& stats);

	Information(std::ifstream& read);
	void writeToFile(std::ofstream& write)const;

	const Battle& getBattle()const;
	const CharacterStats& getStats()const;

	
private:
	Battle battle;
	CharacterStats statsAfterBattle;
};

