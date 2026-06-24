#include "Information.h"

Information::Information(const Battle& battle, const CharacterStats& stats) : battle(battle) , statsAfterBattle(stats)
{
	
}

Information::Information(std::ifstream& read) : battle(read)
{
	read.read(reinterpret_cast<char*>(&this->statsAfterBattle), sizeof(this->statsAfterBattle));

	if (!read)
	{
		throw std::runtime_error("Error");
	}
}
void Information::writeToFile(std::ofstream& write)const
{
	this->battle.writeToFile(write);

	write.write(reinterpret_cast<const char*>(&this->statsAfterBattle), sizeof(this->statsAfterBattle));

	if (!write)
	{
		throw std::runtime_error("Error");
	}
}


const Battle& Information::getBattle()const
{	
	return this->battle;
}

const CharacterStats& Information::getStats()const
{
	return this->statsAfterBattle;
}