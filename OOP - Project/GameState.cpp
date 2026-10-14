#include "GameState.h"
#include <iostream>
#include "SafeInputReading.h"
#include <fstream>


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
			if (dungeonName == this->nameOfDungeons[i])
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

void GameState::selectHeroesToEnterDungeon()
{

}

bool GameState::enterDungeon(const std::string& nameOfDungeon)
{
	return false;
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