#include "GameState.h"
#include <iostream>
#include "SafeInputReading.h"
#include <fstream>
#include "StringHelpers.h"
#include "HeroesState.h"
#include "HeroManagerState.h"
#include <stdexcept>

//bool GameState::isHeroAlreadyLoaded(const std::string& name)const
//{
//	size_t size = this->loadedHeroes.size();
//	for (size_t i = 0; i < size; ++i)
//	{
//		if (this->loadedHeroes[i]->getName() == name)
//		{
//			return true;
//		}
//	}
//	return false;
//}



//Hero* GameState::getLoadedHero(const std::string& name)const
//{
//	size_t size = this->loadedHeroes.size();
//	for (size_t i = 0; i < size; ++i)
//	{
//		if (this->loadedHeroes[i]->getName() == name)
//		{
//			return this->loadedHeroes[i];
//		}
//	}
//	return nullptr;
//}

GameState::GameState(const std::string& nameOfGame)
{
	std::ifstream account(nameOfGame, std::ios::binary);
	if (!account.is_open())
	{
		throw std::exception();
	}
	this->nameOfGame = nameOfGame;

	try
	{
		readStrings(account, this->namesOfHeroes);
		readStrings(account, this->nameOfDungeons);
		readStrings(account, this->nameOfCompletedDungeons);
	}
	catch (...)
	{
		account.close();
		throw;
	}
	account.close();
}
int GameState::display()
{
	while (true)
	{
		std::cout << "Select:\n";
		std::cout << "1.Show names of created heroes\n";
		std::cout << "2.Show names of dungeons you can enter\n";
		std::cout << "3.Show information of a particular dungeon\n";
		std::cout << "4.Show names of dungeons you have completed\n";
		std::cout << "5.Create a new hero\\Remove a hero\n";
		std::cout << "6.Manage items of heroes\n";
		std::cout << "7.Enter a dungeon\n";
		std::cout << "8.Save and back\n";
		int action = 0;
		if (!readValidInt(1, 8, action))
		{
			if (!tryAgain("Wrong input"))
			{
				return 8;
			}
			else
			{
				continue;
			}
		}
		switch (action)
		{
		case 1:
			printNameOfHeroes();
			continue;
		case 2:
			printNameOfDungeons();
			continue;
		case 3:
			dungeonInfo();
			continue;
		case 4:
			printNameOfCompletedDungeons();
			continue;
		case 5:
			return 5;
		case 6:
			return 6;
		case 7:
			return 7;
		case 8:
			return 8;

		}

	}
}

SystemState* GameState::execute(int action)
{
	switch (action)
	{
	case 5:
		return new (std::nothrow) HeroManagerState(this->namesOfHeroes);
	case 6:
		return new (std::nothrow) HeroesState(this->namesOfHeroes);
	case 7:
		//dungeon
		break;
	case 8:
		if (!safeData())
		{
			if (!tryAgain("Could not save progess"))
			{
				changeState();
			}
			return nullptr;
		}
		changeState();
		return nullptr;

	}
}

void GameState::printNameOfHeroes()const
{
	std::cout << "Name of heroes\n";
	printStrings(this->namesOfHeroes);
}


void GameState::printNameOfDungeons() const
{
	std::cout << "Name of dungeons\n";
	printStrings(this->nameOfDungeons);
}

void GameState::dungeonInfo() const
{
	while (true)
	{
		printNameOfDungeons();

		std::string dungeonName = getString("name of dungeon");

		size_t size = this->nameOfDungeons.size();
		for (size_t i = 0; i < size; ++i)
		{
			if (areEqual(dungeonName , this->nameOfDungeons[i]))
			{
				Dungeon* dungeon = loadDungeon(dungeonName);
				// write a info method for dungeon;
				delete dungeon;
				return;
				
			}
		}

		if (!tryAgain("No dungeon with that name exists"))
		{
			return;
		}
	}
}

std::vector<std::string> GameState::selectHeroesToEnterDungeon()
{
	size_t size = this->namesOfHeroes.size();
	std::vector<std::string> heroes;
	if (size == 0)
	{
		std::cout << "No heroes.\n\n\n";
		return heroes;
	}

	while (true)
	{
		if (heroes.size() == 4)
		{
			return heroes;
		}

		std::cout << heroes.size() << " heroes already selected. Do you wish to select another hero?\n";
		int command = 0;
		std::cout << "1.Yes\n";
		std::cout << "2.No\n";
		if (!readValidInt(1, 1, command))
		{
			return heroes;
		}

		std::cout << "Select up to 4 heroes to enter dungeon:\n";
		printNameOfHeroes();

		std::string hero = getString("name of hero");

		if (!doesStringExist(hero, this->namesOfHeroes))
		{
			if (!tryAgain("No hero with such name exists"))
			{
				return heroes;
			}
		}
		else if (doesStringExist(hero, heroes))
		{
			if (!tryAgain("Hero is already selected"))
			{
				return heroes;
			}
		}
		else
		{
			heroes.push_back(hero);
		}

	}
}

const std::string& GameState::selectDungeonToEnter()
{
	std::string dungeonToEnter;
	while (true)
	{
		std::cout << "Dungeons you can enter:\n";
		printNameOfDungeons();
		dungeonToEnter = getString("name of dungeon you want to enter");
		if (doesStringExist(dungeonToEnter, this->nameOfDungeons))
		{
			return dungeonToEnter;
		}

		if (tryAgain("No dungeon with that name exists"))
		{
			continue;
		}

		break;
	}

	return dungeonToEnter;
}


void GameState::printStrings(const std::vector<std::string>& strings)
{
	size_t size = strings.size();
	if (size == 0)
	{
		std::cout << "Empty\n";
	}
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << strings[i] << '\n';
	}
	std::cout << "\n\n\n";
}

void GameState::printNameOfCompletedDungeons()const
{
	std::cout << "Name of completed dungeons\n";
	printStrings(this->nameOfCompletedDungeons);
}

bool GameState::safeData()const
{
	std::ofstream toStore(this->nameOfGame, std::ios::binary);
	if (!toStore.is_open())
	{
		return false;
	}

	try
	{
		writeStrings(toStore, this->namesOfHeroes);
		writeStrings(toStore, this->nameOfDungeons);
		writeStrings(toStore, this->nameOfCompletedDungeons);
	}
	catch (...)
	{
		toStore.close();
		return false;
	}

	toStore.close();
	return true;
}

Dungeon* GameState::loadDungeon(const std::string& nameOfDungeon)const
{
	std::ifstream dungeonFile(nameOfDungeon, std::ios::binary);
	if (!dungeonFile.is_open())
	{
		return nullptr;
	}

	Dungeon* dungeon = new (std::nothrow) Dungeon(dungeonFile);
	if (!dungeon)
	{
		dungeonFile.close();
		return nullptr;
	}

	dungeonFile.close();
	return dungeon;
}