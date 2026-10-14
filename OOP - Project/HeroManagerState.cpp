#include "HeroManagerState.h"
#include <iostream>
#include "Classes.h"
#include "SafeInputReading.h"
#include "Hero.h"
#include "HeroFactory.h"
#include <stdexcept>

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

	Hero* toAdd = HeroFactory::createNewHero(heroName, heroClass); // make so all factories, in case of new fail ,return nullptr instead of throwing and exception
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

		if (!doesHeroExist(name , heroNames))
		{
			return name;
		}

		if (!tryAgain("Name is already taken"))
		{
			return "";
		}

	}
}
bool HeroManagerState::doesHeroExist(const std::string& heroName, const std::vector<std::string>& heroNames)
{
	size_t size = heroNames.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (heroNames[i] == heroName)
		{
			return true;
		}
	}
	return false;
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
