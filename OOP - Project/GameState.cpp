#include "GameState.h"
#include <iostream>
#include "HeroFactory.h"
#include <stdexcept>

void GameState::addNewHero(const std::string& name, HeroClass heroClass)
{
	
	Hero* toAdd = HeroFactory::createNewHero(name, heroClass); // make so all factories, in case of new fail ,return nullptr instead of throwing and exception
	if (!toAdd)
	{
		std::cout << "Could not create hero\n";
		return;
	}

	size_t numberOfheroes = this->namesOfHeroes.size();
	size_t numberOfCurrentHeroes = this->heroes.size();
	try
	{
		this->namesOfHeroes.resize(numberOfheroes + 1);

		this->heroes.resize(numberOfCurrentHeroes + 1);

		std::ofstream fileOfHero(name, std::ios::binary);
		if (!fileOfHero.is_open())
		{
			throw std::exception();
		}

		toAdd->writeToFile(fileOfHero);
		fileOfHero.close();

		this->namesOfHeroes[numberOfheroes] = name;
		this->heroes[numberOfCurrentHeroes] = toAdd;
	
	}
	catch (...)
	{
		delete toAdd;
		this->namesOfHeroes.resize(numberOfheroes);
		this->heroes.resize(numberOfCurrentHeroes);
		std::cout << "Could not create hero\n";
		std::remove(name.c_str());
	}

}
Hero* GameState::loadHeroData(const std::string& name)
{
	std::ifstream heroFile(name, std::ios::binary);
	if (!heroFile.is_open())
	{
		return nullptr;
	}

	uint32_t heroClassValue = 0;
	heroFile.read(reinterpret_cast<char*>(&heroClassValue), sizeof(heroClassValue));

	HeroClass type = static_cast<HeroClass>(heroClassValue);

	Hero* toStore = HeroFactory::loadHeroFromFile(heroFile, type);
	if (!toStore)
	{
		return nullptr;;
	}
	heroFile.close();
	
	return toStore;
}
void GameState::heroInfo(const std::string& nameOfHero)
{
	size_t size = this->namesOfHeroes.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (this->namesOfHeroes[i] == nameOfHero)
		{
			size_t loadedHeroes = this->heroes.size();
			for (size_t i = 0; i < loadedHeroes; ++i)
			{
				if (this->heroes[i]->getName() == nameOfHero)
				{
					// in hero add a function that prints the information of the hero
					return;
				}
			}

			Hero* hero = loadHeroData(nameOfHero);

			if (hero)
			{
				// in hero add a function that prints the information of the hero
				try
				{
					this->heroes.push_back(hero);
				}
				catch (...)
				{
					delete hero;
				}
			}
			else
			{
				std::cout << "Failed to load hero data" << "\n\n\n";
			}

			return;
		}
	}
	std::cout << "No hero with that name exists" << "\n\n\n";
}

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

void GameState::manageItems(const std::string& firstHero, const std::string& secondHero)
{
}

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
