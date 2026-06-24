#include "Information.h"

Information::Information(const Battle& battle, const CharacterStats& stats) : battle(battle) , statsAfterBattle(stats)
{
	
}


const Battle& Information::getBattle()const
{	
	return this->battle;
}

const CharacterStats& Information::getStats()const
{
	return this->statsAfterBattle;
}