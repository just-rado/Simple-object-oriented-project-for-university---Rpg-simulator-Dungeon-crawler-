#include "Battle.h"

uint64_t Battle::nextID = 0;


Battle::Battle(const std::string& nameOfRoom, const std::vector<std::string>& namesOfHeroes, const std::vector<uint64_t>& IDsOfEnemies) :
	ID(nextID), nameOfRoom(nameOfRoom), namesOfHeroes(namesOfHeroes), IDsOfEnemies(IDsOfEnemies)
{
	++nextID;
}

Battle::Battle(const Battle& other): ID(nextID), nameOfRoom(other.nameOfRoom), namesOfHeroes(other.namesOfHeroes), 
					IDsOfEnemies(other.IDsOfEnemies)
{
	++nextID;
}

uint64_t Battle::getID()const
{
	return this->ID;
}

size_t Battle::getNumberOfHeroes()const
{
	return this->namesOfHeroes.size();
}
size_t Battle::getNumberOfEnemies()const
{
	return this->IDsOfEnemies.size();
}

const std::string& Battle::getNameOfHero(size_t index)const
{
	return this->namesOfHeroes[index];
}
uint64_t Battle::getIdOfEnemy(size_t index)const
{
	return this->IDsOfEnemies[index];
}