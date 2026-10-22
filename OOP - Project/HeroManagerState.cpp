#include "HeroManagerState.h"
#include <iostream>
#include "Classes.h"
#include "SafeInputReading.h"
#include "Hero.h"
#include "HeroFactory.h"
#include <stdexcept>
#include "StringHelpers.h"


HeroManagerState::HeroManagerState(std::vector<std::string>& heroNames)
{
	while (true)
	{
		std::cout << "Choose\n";
		std::cout << "1.Create a new hero\n";
		std::cout << "2.Remove a hero\n";
		std::cout << "3.Back\n";

		int action = 0;
		if (!readValidInt(1, 3, action))
		{
			if (!tryAgain("Wrong input"))
			{
				break;
			}
			else
			{
				continue;
			}
		}

		switch (action)
		{
		case 1:
			createNewhero(heroNames);
			continue;
		case 2:
			removeAHero(heroNames);
			continue;
		case 3:
			break;
	
		}
	}
}

int HeroManagerState::display()
{
	return 1;
}

SystemState* HeroManagerState::execute(int action)
{
	changeState();
	return nullptr;
}
void HeroManagerState::createNewhero(std::vector<std::string>& heroNames)
{
	std::string heroName = inputNewHeroName(heroNames);
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

	Hero* toAdd = HeroFactory::createNewHero(heroName, heroClass); 
	if (!toAdd)
	{
		std::cout << "Could not create hero\n";
		return;
	}

	size_t numberOfheroes = heroNames.size();

	try
	{
		heroNames.resize(numberOfheroes + 1);

		std::ofstream fileOfHero(heroName, std::ios::binary);
		if (!fileOfHero.is_open())
		{
			throw std::exception();
		}

		toAdd->writeToFile(fileOfHero);
		fileOfHero.close();

		heroNames[numberOfheroes] = heroName;
	}
	catch (...)
	{
		delete toAdd;
		heroNames.resize(numberOfheroes);
		std::cout << "Could not create hero\n";
		std::remove(heroName.c_str());
		return;
	}
	delete toAdd;
}
void HeroManagerState::removeAHero(std::vector<std::string>& heroNames)
{
	while (true)
	{
		std::cout << "Name of heroes:\n";
		size_t size = heroNames.size();
		for (size_t i = 0; i < size; ++i)
		{
			std::cout << heroNames[i] << '\n';
		}

		std::string toRemove = getString("name of hero you want to remove");

		for (size_t i = 0; i < size; ++i)
		{
			if (toRemove == heroNames[i])
			{
				std::remove(toRemove.c_str());
				heroNames.erase(heroNames.begin() + i);
				return;
			}
		}

		if (!tryAgain("No hero with that name exists"))
		{
			return;
		}

	}
}

std::string HeroManagerState::inputNewHeroName(const std::vector<std::string>& heroNames)
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

		if (!doesStringExist(name , heroNames))
		{
			return name;
		}

		if (!tryAgain("Name is already taken"))
		{
			return "";
		}

	}
}

bool HeroManagerState::isBlank(const std::string& string)
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
