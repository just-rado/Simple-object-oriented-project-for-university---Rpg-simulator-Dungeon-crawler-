#pragma once
#include <string>
#include <vector>
#include <fstream>

class Battle
{
public:

	Battle(const std::string& nameOfRoom, const std::vector<std::string>& namesOfHeroes, const std::vector<uint64_t>& IDsOfEnemies);
	
	Battle(std::ifstream& read);
	void writeToFile(std::ofstream& write)const;

	uint64_t getID()const;

	static void writeNextID(std::ofstream& write);
	static void setNextID(std::ifstream& read);

	size_t getNumberOfHeroes()const;
	size_t getNumberOfEnemies()const;

	const std::string& getNameOfHero(size_t index)const;
	uint64_t getIdOfEnemy(size_t index)const;


private:
	uint64_t ID;
	std::string nameOfRoom;
	std::vector<std::string> namesOfHeroes;
	std::vector<uint64_t> IDsOfEnemies;

	

	static uint64_t nextID;
};

