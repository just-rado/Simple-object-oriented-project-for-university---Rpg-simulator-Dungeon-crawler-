#include "GameState.h"
#include <iostream>
#include "HeroFactory.h"
#include <stdexcept>
#include "Classes.h"
#include "HeroesState.h"
#include "SafeInputReading.h"


bool GameState::isBlank(const std::string& string)
{
	for (unsigned char c : string)
	{
		if (!std::isspace(c))
		{
			return false;
		}
	}
	return true;
}

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

bool GameState::doesHeroExist(const std::string& name)const
{
	size_t size = this->namesOfHeroes.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (this->namesOfHeroes[i] == name)
		{
			return true;
		}
	}
	return false;
}

std::string GameState::inputNewHeroName()const
{
	std::string name;
	while (true)
	{
		name = getString("name of new hero");

		if (isBlank(name))
		{
			std::cout << "Name cannot be empty\n";
			continue;
		}
		
		if (!doesHeroExist(name))
		{
			return name;
		}

		if (!tryAgain("Name is already taken"))
		{
			return "";
		}
		
	}
}



void GameState::addNewHero()
{
	std::string heroName = inputNewHeroName();
	if (heroName.empty())
	{
		return;
	}
	
	HeroClass heroClass = HeroClass::NUM_CLASSES;
	while (true)
	{
		std::cout << "Enter class of hero:\n";
		printClasses();
		int cl = 0;
		int lastValidHeroClass = static_cast<int>(HeroClass::NUM_CLASSES) - 1;
		if (!readValidInt(0, lastValidHeroClass, cl))
		{
			if (tryAgain("Unknown class"))
			{
				continue;
			}
			else
			{
				return;
			}
		}
		heroClass = static_cast<HeroClass>(cl);
		break;
	}
	
	Hero* toAdd = HeroFactory::createNewHero(heroName, heroClass); // make so all factories, in case of new fail ,return nullptr instead of throwing and exception
	if (!toAdd)
	{
		std::cout << "Could not create hero\n";
		return;
	}

	size_t numberOfheroes = this->namesOfHeroes.size();

	try
	{
		this->namesOfHeroes.resize(numberOfheroes + 1);

		std::ofstream fileOfHero(heroName, std::ios::binary);
		if (!fileOfHero.is_open())
		{
			throw std::exception();
		}

		toAdd->writeToFile(fileOfHero);
		fileOfHero.close();

		this->namesOfHeroes[numberOfheroes] = heroName;
	}
	catch (...)
	{
		delete toAdd;
		this->namesOfHeroes.resize(numberOfheroes);
		std::cout << "Could not create hero\n";
		std::remove(heroName.c_str());
		return;
	}
	delete toAdd;
}


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
	size_t size = this->namesOfHeroes.size();
	if (size == 0)
	{
		std::cout << "No heroes" << "\n\n\n";
		return;
	}

	for (size_t i = 0; i < size; ++i)
	{
		std::cout << this->namesOfHeroes[i] << '\n';
	}
	std::cout << "\n\n\n";
}

void GameState::manageItemsBetweenTwoHeroes(const Hero* firstHero, const Hero* secondHero)
{
	while (true)
	{
		std::cout << "Choose action:\n";
	}
	
}

void GameState::manageItemsOfASingleHero(const Hero* hero)
{

}



//void GameState::manageItems()
//{
//	std::cout << "Do you wish to switch items between two characters";
//	std::cout << "1.Yes";
//	std::cout << "2.No";
//
//	int command = 0;
//	std::cin >> command;
//	if (command == 1)
//	{
//		std::string firstHeroName = getString("name of first hero");
//		std::string secondHeroName = getString("name of second hero");
//
//		if (firstHeroName == secondHeroName)
//		{
//			return;
//		}
//
//		bool firstExists = false;
//		bool secondExists = false;
//
//		size_t size = this->namesOfHeroes.size();
//		for (size_t i = 0; i < size; ++i)
//		{
//			if (!firstExists && this->namesOfHeroes[i] == firstHeroName)
//			{
//				firstExists = true;
//			}
//			else if (!secondExists && this->namesOfHeroes[i] == secondHeroName)
//			{
//				secondExists = true;
//			}
//
//			if (firstExists && secondExists)
//			{
//				break;
//			}
//
//		}
//
//		if (!firstExists || !secondExists)
//		{
//			return;
//		}
//
//		Hero* firstHero  = nullptr;
//		
//		firstHero = loadHeroData(firstHeroName);
//		
//
//		if (!firstHero)
//		{
//			std::cout << "Could not load first hero\n\n\n";
//			return;
//		}
//
//		Hero* secondHero = nullptr;
//
//		secondHero = loadHeroData(secondHeroName);
//		
//		if (!secondHero)
//		{
//			std::cout << "Could not load second hero\n\n\n";
//			return;
//		}
//
//
//		manageItemsBetweenTwoHeroes(firstHero, secondHero);
//	}
//
//	if (command == 2)
//	{
//
//	}
//	
//}

void GameState::dungeonInfo() const
{

}

void GameState::printNameOfDungeons() const
{

}

void GameState::selectHeroesToEnterDungeon()
{

}

bool GameState::enterDungeon(const std::string& nameOfDungeon)
{
	return false;
}
