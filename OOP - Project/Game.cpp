#include "Game.h"
#include "StringFunctionsForFiles.h"
#include "Warrior.h"
#include "Mage.h"
#include "Healer.h"
#include "Paladin.h"
#include <iostream>


Game::Game(std::string& nameOfGame)
{
	this->nameOfGame = nameOfGame;
	this->nameOfDungeons.push_back("depths");
	gameStart();
}

Game::Game(std::ifstream& read)
{
	this->nameOfGame = readString(read);

	
	uint32_t numberOfHeroes = 0;
	read.read(reinterpret_cast<char*>(&numberOfHeroes), sizeof(numberOfHeroes));
	if (numberOfHeroes > 0)
	{
		this->namesOfHeroes.resize(numberOfHeroes);
		for (uint32_t i = 0; i < numberOfHeroes; ++i)
		{
			this->namesOfHeroes[i] = readString(read);
		}


	}

	uint32_t numberOfDungeons = 0;
	
	read.read(reinterpret_cast<char*>(&numberOfDungeons), sizeof(numberOfDungeons));
	if (numberOfDungeons > 0)
	{
		this->nameOfDungeons.resize(numberOfDungeons);
		for (uint32_t i = 0; i < numberOfDungeons; ++i)
		{
			this->nameOfDungeons[i] = readString(read);
		}

	}

	this->currentDungeon = nullptr;
	gameStart();
}


bool Game::loadHeroData(size_t index)
{
	if (index >= this->namesOfHeroes.size())
	{
		return false;
	}


	std::ifstream heroFile(this->namesOfHeroes[index], std::ios::binary);
	if (!heroFile.is_open())
	{
		return false;
	}
	
	

	Hero* toStore = nullptr;
	uint32_t heroClassValue = 0;
	heroFile.read(reinterpret_cast<char*>(&heroClassValue), sizeof(heroClassValue));

	HeroClass type = static_cast<HeroClass>(heroClassValue);

	switch (type)
	{
	case HeroClass::WARRIOR:
		toStore = new Warrior(heroFile);
		break;
	case HeroClass::MAGE:
		toStore = new Mage(heroFile);
		break;
	case HeroClass::HEALER:
		toStore = new Healer(heroFile);
		break;
	case HeroClass::PALADIN:
		toStore = new Paladin(heroFile);
		break;
	default:
		return false;
	}
	heroFile.close();
	try
	{
		this->heroes.push_back(toStore);
	}
	catch (...)
	{
		delete toStore;
		return false;
	}
	
	return true;
}

bool Game::addNewHero(std::string name, HeroClass heroClass)
{
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
		std::cout << "No such hero class exists";
		return false;
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
			std::cout << "Could not create hero file\n";
			return false;
		}
		
		toAdd->writeToFile(fileOfHero);
		fileOfHero.close();

		this->namesOfHeroes[numberOfheroes] = name;
		std::cout << numberOfheroes << "\n\n\n";

	}
	catch (...)
	{
		delete toAdd;
		this->namesOfHeroes.resize(numberOfheroes);
		this->heroes.resize(numberOfCurrentHeroes);
		std::cout << "Could not create hero\n";
		std::remove(name.c_str());
		return false;
	}
	delete toAdd;
	return true;
}

void Game::addNewDungeon(std::string name)
{
	if (!isNameValid(name))
	{
		return;
	}
	this->nameOfDungeons.push_back(name);
}

bool Game::loadDungeon(size_t index)
{
	if (index >= this->nameOfDungeons.size())
	{
		return false;
	}
	Dungeon* toLoad = nullptr;
	std::ifstream dungeonFile(this->nameOfDungeons[index], std::ios::binary);
	if (!dungeonFile.is_open())
	{
		return false;
	}
	try
	{
		toLoad = new Dungeon(dungeonFile);
	}
	catch (...)
	{
		delete toLoad;
		return false;
	}
	
	
	delete this->currentDungeon;

	this->currentDungeon = toLoad;
	return true;
}


void Game::gameStart()
{
	while (true)
	{
		std::cout << "Options:\n" << "1.Create new hero\n" << "2.Show current dungeons\n" << "3.Select 4 heroes and enter a dungeon\n"
			<<"4. Save game and quit\n\n\n\n";
		int option = 0;
		std::cin >> option;
		if (option == 1)
		{
			bool created = false;
			while (!created)
			{
				std::string nameOfhero;
				std::cout << "Enter name of new Hero:";
				std::cin >> nameOfhero;

				if (!isNameValid(nameOfhero))
				{
					std::cout << "Invalid name of hero\n";
					std::cout << "Do you wish to try again.\n" << "1.Yes\n" << "2.No";
					int exit = 0;
					std::cin >> exit;
					if (exit == 2)
					{
						break;
					}
					continue;
				}

				size_t numberOfheroes = this->namesOfHeroes.size();
				for (size_t i = 0; i < numberOfheroes; ++i)
				{
					if (this->namesOfHeroes[i] == nameOfhero)//fix 
					{
						std::cout << "Hero with that name already exists\n";
						std::cout << "Do you wish to try again.\n" << "1.Yes\n" << "2.No";
						int exit = 0;
						std::cin >> exit;
						if (exit == 2)
						{
							break;
						}
						continue;
					}
				}

				std::cout << "Choose class of hero:\n" << "1.Warrior\n" << "2.Mage\n" << "3.Healer\n" << "4.Paladin";
				int heroClass = 0;
				std::cin >> heroClass;
				HeroClass type = static_cast<HeroClass>(heroClass - 1);
				
				created = addNewHero(nameOfhero, type);
				if (!created)
				{
					std::cout << "Do you wish to try again.\n" << "1.Yes\n" << "2.No";
					int exit = 0;
					std::cin >> exit;
					if (exit == 2)
					{
						break;
					}
					continue;
				}

			}
		
		}
		else if (option == 2)
		{
			size_t size = this->nameOfDungeons.size();
			for (size_t i = 0; i < size; ++i)
			{
				std::cout << this->nameOfDungeons[i] << '\n';
			}
		}
		else if (option == 3)
		{
			size_t size = this->namesOfHeroes.size();
			if (size < 4)
			{
				std::cout << "Not enough heroes to enter dungeon\n";
				std::cout << "Current number of heroes: " << size << '\n';
				continue;
			}
			storeCurrentHeroes();

			size_t chosen = 0;
			while (chosen < 4)
			{
				std::cout << "Choose a hero:\n" << "Current heroes are:\n";
				for (size_t i = 0; i < size; ++i)
				{
					std::cout << i + 1 << ". " << this->namesOfHeroes[i] << '\n';
				}
				int number = 0;
				std::cin >> number;
				std::cout << '\n';

				if (number < 1 || number > size)
				{
					std::cout << "Hero does not exist\n";
					continue;
				}

				bool loadedHero = loadHeroData(number - 1);
				if (!loadedHero)
				{
					std::cout << "Could not pick hero\n";
					std::cout << "Do you wish to try again.\n" << "1.Yes\n" << "2.No";
					int exit = 0;
					std::cin >> exit;
					if (exit == 2)
					{
						break;
					}
					continue;
				}
				++chosen;

			}
			

			std::cout << "Pick dungeon:\n";
			size_t numberOfDungeons = this->nameOfDungeons.size();
			if (numberOfDungeons == 0)
			{
				std::cout << "No dungeons\n";
				continue;
			}
			for (size_t i = 0; i < numberOfDungeons; ++i)
			{
				std::cout << i + 1 << ". " << this->nameOfDungeons[i] << '\n';
			}

			while (true)
			{
				int dungeon = 0;
				std::cin >> dungeon;

				if (dungeon < 1 || dungeon > numberOfDungeons)
				{
					std::cout << "Dungeon does not exist\n";
					continue;
				}

				bool loadedDungeon = loadDungeon(dungeon - 1);
				if (!loadedDungeon)
				{
					std::cout << "Could not enter dungeon\n";
					std::cout << "Do you wish to try again.\n" << "1.Yes\n" << "2.No";
					int exit = 0;
					std::cin >> exit;
					if (exit == 2)
					{
						storeCurrentHeroes();
						break;
					}
					continue;
				}
				break;
			}
			
			this->currentDungeon->enter(this->heroes);
			
		}
		else if (option == 4)
		{
			
			storeCurrentHeroes();
			if (this->currentDungeon)
			{
				delete this->currentDungeon;
				this->currentDungeon = nullptr;
			}
			std::ofstream saveGame(this->nameOfGame, std::ios::binary);
			if (!saveGame.is_open())
			{
				throw std::runtime_error("Eror");
			}
			storeGame(saveGame);
			saveGame.close();
			break;
		}
		else if (option == 5)
		{
			storeCurrentHeroes();
			for (size_t i = 0; i < this->namesOfHeroes.size(); ++i)
			{
				loadHeroData(i);
			}
			printInfoOfHeroes();
		}
	}
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

void Game::storeCurrentHeroes()
{
	size_t size = this->heroes.size();

	try
	{
		for (size_t i = 0; i < size; ++i)
		{
			if (this->heroes[i] && this->heroes[i]->getHP() > 0)
			{
				std::ofstream store(this->heroes[i]->getName(), std::ios::binary);
				if (!store.is_open())
				{
					throw std::runtime_error("Error");
				}
				this->heroes[i]->writeToFile(store);
				store.close();
				delete this->heroes[i];
				this->heroes[i] = nullptr;
			}
			else if (this->heroes[i])
			{
				for (size_t j = 0; j < this->namesOfHeroes.size(); ++j)
				{
					if (this->heroes[i]->getName() == this->namesOfHeroes[j])
					{
						this->namesOfHeroes.erase(this->namesOfHeroes.begin() + j);
					}
				}
			}
		}
	}
	catch (...)
	{
		for (size_t i = 0; i < size; ++i)
		{
			delete this->heroes[i];
		}
	}
	this->heroes.clear();
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

void Game::printInfoOfHeroes()const
{
	for (size_t i = 0; i < this->heroes.size(); ++i)
	{
		if (this->heroes[i])
		{
			std::cout << this->heroes[i]->getName() << "  " << this->heroes[i]->getHP() << '\n';
		}
	}
}