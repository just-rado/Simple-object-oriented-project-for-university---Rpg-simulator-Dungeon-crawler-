#pragma once
#include <string>
#include <vector>

class Battle
{
public:

	Battle(const std::string& nameOfRoom, const std::vector<std::string>& namesOfHeroes, const std::vector<uint64_t>& IDsOfEnemies);
	

	uint64_t getID()const;

	size_t getNumberOfHeroes()const;
	size_t getNumberOfEnemies()const;

	const std::string& getNameOfHero(size_t index)const;
	uint64_t getIdOfEnemy(size_t index)const;


private:
	const uint64_t ID;
	std::string nameOfRoom;
	std::vector<std::string> namesOfHeroes;
	std::vector<uint64_t> IDsOfEnemies;

	static bool setNextID(uint64_t ID);

	static uint64_t nextID;
};

