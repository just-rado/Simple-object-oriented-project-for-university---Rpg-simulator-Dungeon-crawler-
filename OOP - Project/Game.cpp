#include "Game.h"
#include "StringFunctionsForFiles.h"
#include "Warrior.h"
#include "Mage.h"
#include "Healer.h"
#include "Paladin.h"


Game::Game(std::ifstream& read)
{
	this->nameOfGame = readString(read);

	uint32_t numberOfHeroes = 0;
	read.read(reinterpret_cast<char*>(&numberOfHeroes), sizeof(numberOfHeroes));

	if (numberOfHeroes > 0)
	{
		for (uint32_t i = 0; i < numberOfHeroes; ++i)
		{
			this->namesOfHeroes[i] = readString(read);
		}


	}

	uint32_t numberOfDungeons = 0;
	read.read(reinterpret_cast<char*>(&numberOfDungeons), sizeof(numberOfDungeons));
	if (numberOfDungeons > 0)
	{
		for (uint32_t i = 0; i < numberOfDungeons; ++i)
		{
			this->nameOfDungeons[i] = readString(read);
		}

	}

	this->currentDungeon = nullptr;
}


void Game::loadHeroData(size_t index)
{
	if (index >= this->namesOfHeroes.size())
	{
		return;
	}

	std::ifstream heroFile(this->namesOfHeroes[index], std::ios::binary);
	if (!heroFile.is_open())
	{
		return;
	}

	Hero* toStore = nullptr;
	uint32_t heroClassValue = 0;
	heroFile.read(reinterpret_cast<char*>(&heroClassValue), sizeof(heroClassValue));

	HeroClass type = static_cast<HeroClass>(heroClassValue);

	switch (type)
	{
	case HeroClass::WARRIOR:
		toStore = new Warrior(heroFile);
	case HeroClass::MAGE:
		toStore = new Mage(heroFile);
	case HeroClass::HEALER:
		toStore = new Healer(heroFile);
		break;
	case HeroClass::PALADIN:
		toStore = new Paladin(heroFile);
		break;
	case HeroClass::NUM_CLASSES:
		break;
	default:
		break;
	}
	try
	{
		this->heroes.push_back(toStore);
	}
	catch (...)
	{
		delete toStore;
		throw;
	}

}

void Game::addNewHero(std::string name, HeroClass heroClass)
{
	if (name.empty())
	{
		return;
	}

	for (char c : name)
	{
		if (!std::isalnum(static_cast<unsigned char>(c)) && c != '_' && c != '-')
		{
			return;
		}
	}

	size_t numberOfheroes = this->namesOfHeroes.size();
	for (size_t i = 0; i < numberOfheroes; ++i)
	{
		if (this->namesOfHeroes[i] == name)
		{
			
			return;
		}
	}
	Hero* toAdd = nullptr;
	switch (heroClass)
	{
	case HeroClass::WARRIOR:
		toAdd = new Warrior(name);
		break;
	case HeroClass::MAGE:
		toAdd = new Mage(name);
		break;
	case HeroClass::HEALER:
		toAdd = new Healer(name);
		break;
	case HeroClass::PALADIN:
		toAdd = new Paladin(name);
		break;
	default:
		return;
	}
	size_t numberOfCurrentHeroes = this->heroes.size();
	try
	{
	
		std::ofstream fileOfHero(name, std::ios::binary);
		if (!fileOfHero.is_open())
		{
			throw std::runtime_error("Error");
		}
		fileOfHero.close();

		this->namesOfHeroes.resize(numberOfheroes + 1);
		
		this->heroes.resize(numberOfCurrentHeroes + 1);
		
		this->namesOfHeroes[numberOfheroes] = name;
		this->heroes[numberOfCurrentHeroes] = toAdd;

	}
	catch (...)
	{
		this->namesOfHeroes.resize(numberOfheroes);
		this->heroes.resize(numberOfCurrentHeroes);
		delete toAdd;
	}

}

void Game::addNewDungeon(std::string name)
{
	if (name.empty())
	{
		return;
	}

	for (char c : name)
	{
		if (!std::isalnum(static_cast<unsigned char>(c)) && c != '_' && c != '-')
		{
			return;
		}
	}
	this->nameOfDungeons.push_back(name);
}

void Game::loadDungeon(size_t index)
{
	if (index >= this->nameOfDungeons.size())
	{
		return;
	}

	std::ifstream dungeonFile(this->namesOfHeroes[index], std::ios::binary);
	if (!dungeonFile.is_open())
	{
		return;
	}
	Dungeon* toLoad = new Dungeon(dungeonFile);
	
	delete this->currentDungeon;

	this->currentDungeon = toLoad;
}


void Game::storeGame(std::ofstream& write)const
{
	writeString(write, this->nameOfGame);

	uint32_t numberOfNamesOfHeroes = static_cast<uint32_t>(this->namesOfHeroes.size());
	write.write(reinterpret_cast<const char*>(&numberOfNamesOfHeroes), sizeof(numberOfNamesOfHeroes));

	for (uint32_t i = 0; i < numberOfNamesOfHeroes; ++i)
	{
		writeString(write, this->namesOfHeroes[i]);
	}

	uint32_t numberOfNameOfDungeons = static_cast<uint32_t>(this->nameOfDungeons.size());
	write.write(reinterpret_cast<const char*>(&numberOfNameOfDungeons), sizeof(numberOfNameOfDungeons));

	for (uint32_t i = 0; i < numberOfNameOfDungeons; ++i)
	{
		writeString(write, this->nameOfDungeons[i]);
	}
}

Game::~Game()
{
	size_t numberOfHeroes = this->heroes.size();
	for (size_t i = 0; i < numberOfHeroes; ++i)
	{
		delete this->heroes[i];
	}
	this->heroes.clear();

	delete this->currentDungeon;
	this->currentDungeon = nullptr;
}