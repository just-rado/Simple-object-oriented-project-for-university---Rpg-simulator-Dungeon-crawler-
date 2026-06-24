#include "Battle.h"
#include "StringFunctionsForFiles.h"

uint64_t Battle::nextID = 1;


Battle::Battle(const std::string& nameOfRoom, const std::vector<std::string>& namesOfHeroes, const std::vector<uint64_t>& IDsOfEnemies) :
	ID(nextID), nameOfRoom(nameOfRoom), namesOfHeroes(namesOfHeroes), IDsOfEnemies(IDsOfEnemies)
{
	++nextID;
}

Battle::Battle(std::ifstream& read)
{
	read.read(reinterpret_cast<char*>(&this->ID), sizeof(this->ID));

	this->nameOfRoom = readString(read);

	uint32_t numberOfNameOfHeroes = 0;
	read.read(reinterpret_cast<char*>(&numberOfNameOfHeroes), sizeof(numberOfNameOfHeroes));

	if (numberOfNameOfHeroes > 0)
	{
		this->namesOfHeroes.resize(numberOfNameOfHeroes);

		for (uint32_t i = 0; i < numberOfNameOfHeroes; ++i)
		{
			std::string temp = readString(read);

			this->namesOfHeroes[i] = std::move(temp);
		}
	}

	uint32_t numberOfEnemyID = 0;
	read.read(reinterpret_cast<char*>(&numberOfEnemyID), sizeof(numberOfEnemyID));

	if (numberOfEnemyID > 0)
	{
		this->IDsOfEnemies.resize(numberOfEnemyID);

		read.read(reinterpret_cast<char*>(this->IDsOfEnemies.data()), numberOfEnemyID * sizeof(uint64_t));
	}

	if (!read)
	{
		throw std::runtime_error("Error");
	}

}
void Battle::writeToFile(std::ofstream& write)const
{
	write.write(reinterpret_cast<const char*>(&this->ID), sizeof(this->ID));

	writeString(write, this->nameOfRoom);

	uint32_t numberOfNameOfHeroes = static_cast<uint32_t>(this->namesOfHeroes.size());
	write.write(reinterpret_cast<const char*>(&numberOfNameOfHeroes), sizeof(numberOfNameOfHeroes));

	for (const std::string& name : this->namesOfHeroes)
	{
		writeString(write, name);
	}

	uint32_t numberOfEnemyID = static_cast<uint32_t>(this->IDsOfEnemies.size());
	write.write(reinterpret_cast<const char*>(&numberOfEnemyID), sizeof(numberOfEnemyID));

	if (numberOfEnemyID > 0)
	{
		write.write(reinterpret_cast<const char*>(this->IDsOfEnemies.data()), numberOfEnemyID * sizeof(uint64_t));
	}

	if (!write)
	{
		throw std::runtime_error("Error");
	}


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

void Battle::setNextID(std::ifstream& read)
{
	read.read(reinterpret_cast<char*>(&nextID), sizeof(nextID));

	if (!read)
	{
		throw std::runtime_error("Error");
	}
}

void Battle::writeNextID(std::ofstream& write)
{
	write.write(reinterpret_cast<const char*>(&nextID), sizeof(nextID));

	if (!write)
	{
		throw std::runtime_error("Error");
	}
}