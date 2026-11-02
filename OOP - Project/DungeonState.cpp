#include "DungeonState.h"
#include <stdexcept>
#include "HeroFactory.h"
#include <iostream>
#include "SafeInputReading.h"
#include <algorithm>
#include <numeric>
#include <random>

DungeonState::DungeonState(const std::string& dungeonName, const std::vector<std::string>& heroesThatWillEnterDungeon,
	std::vector<std::string>& allHeroes)
{
	Dungeon* dungeon = loadDungeonData(dungeonName);
	if (!dungeon)
	{
		std::cout << "Could not load dungeon\n\n\n";
		throw std::runtime_error("Error");
	}
	std::vector<Hero*> heroes;
	try
	{
		heroes = loadHeroes(heroesThatWillEnterDungeon);
	}
	catch (...)
	{
		delete dungeon;
		throw;
	}

	newScreen();
	enterDungeon(heroes, dungeon);

	while (true)
	{
		if (!updateAndSafeData(dungeon, heroes, allHeroes))
		{
			if (!tryAgain("Could not safe data"))
			{
				break;
			}
			continue;
		}
		break;
	}

	delete dungeon;
	freeHeap(heroes, heroes.size());
	
}

void DungeonState::enterDungeon(std::vector<Hero*>& heroes, Dungeon* dungeon)
{
	while (true)
	{
		Room* currentRoom = dungeon->getCurrentRoom();
		if (!currentRoom)
		{
			std::cout << "Dungeon cleared!!!\n";
			break;
		}

		bool allHeroesDied = false;
		enterRoom(heroes, currentRoom , allHeroesDied);
		if (allHeroesDied)
		{
			std::cout << "All heroes died\n";
			break;
		}
		else
		{
			std::cout << "Room cleared\n";
		}
		std::cout << "Do you wish to:\n1.Enter next room\n2.Leave dungeon\n";
		int action = -1;
		while (!readValidInt(1, 2, action))
		{
			std::cout << "Try again\n\n\n";
		}

		if (action == 2)
		{
			break;
		}

		dungeon->nextRoom();
	
	}
}


void DungeonState::enterRoom(std::vector<Hero*>& heroes, Room* room, bool& allHeroesDied)
{
	std::cout << "Battle Started\n";
	static std::mt19937 gen{ std::random_device{}() };
	size_t currentTurn = 1;
	bool allEnemiesDefeated = false;
	while (true)
	{
		std::vector<size_t> heroIndices(heroes.size());
		createRandomTurnOrder(heroIndices , gen);

		std::vector<size_t> enemyIndices(room->getNumberOfEnemies());
		createRandomTurnOrder(enemyIndices, gen);

		
		std::cout << "Current turn: " << currentTurn << "\n\n\n";
		playTurn(heroes, heroIndices , enemyIndices , room, currentTurn , allHeroesDied , allEnemiesDefeated);

		
		newScreen();
		for (size_t i = 0; i < heroes.size(); ++i)
		{
			heroes[i]->printBasicInfo();
		}

		if (allHeroesDied || allEnemiesDefeated)
		{
			break;
		}

		++currentTurn;
	}
}

void DungeonState::playTurn(std::vector<Hero*>& heroes, const std::vector<size_t>& heroIndices, const std::vector<size_t>& enemyIndices,
	Room* room , size_t turn , bool& allHeroesDied , bool& allEnemiesDied)
{
	size_t currentHeroIndex = 0;
	size_t currentEnemyIndex = 0;
	size_t numberOfHeroes = heroIndices.size();
	size_t numberOfEnemies = enemyIndices.size();
	while (currentHeroIndex < numberOfHeroes || currentEnemyIndex < numberOfEnemies)
	{
		if (currentHeroIndex < numberOfHeroes)
		{
			while (currentHeroIndex < numberOfHeroes && heroes[heroIndices[currentHeroIndex]]->getHP() <= 0)
			{
				++currentHeroIndex;
			}
			
			if (currentHeroIndex < numberOfHeroes)
			{
				Hero* currentHero = heroes[heroIndices[currentHeroIndex]];
				heroTurn(heroes, currentHero, room);
			}
			
			++currentHeroIndex;
		}
		
		if (currentEnemyIndex < numberOfEnemies)
		{
			while (currentEnemyIndex < numberOfEnemies && room->getEnemy(enemyIndices[currentEnemyIndex])->getHP() <= 0)
			{
				++currentEnemyIndex;
			}

			if (currentEnemyIndex < numberOfEnemies)
			{
				Enemy* currentEnemy = room->getEnemy(enemyIndices[currentEnemyIndex]);
				enemyTurn(heroes, currentEnemy , turn , currentEnemyIndex);
			}
			++currentEnemyIndex;
		}

		bool foundAlive1 = false;
		for (size_t i = 0; i < numberOfHeroes; ++i)
		{
			if (heroes[i]->getHP() > 0)
			{
				foundAlive1 = true;
				break;
			}
		}

		if (!foundAlive1)
		{
			allHeroesDied = true;
			break;
		}

		bool foundAlive2 = false;
		for (size_t i = 0; i < numberOfEnemies; ++i)
		{
			if (room->getEnemy(i)->getHP() > 0)
			{
				foundAlive2 = true;
				break;
			}
		}
		
		if (!foundAlive2)
		{
			allEnemiesDied = true;
			break;
		}
	}
}


void DungeonState::heroTurn(std::vector<Hero*>& heroes, Hero* hero, Room* room)
{
	std::cout << "Current hero's turn\n";
	hero->printBasicInfo();
	std::cout << "\n\n\n";

	size_t options = 1;
	std::cout << "Choose target:\n";
	std::cout << "1.Enemy\n";
	if (hero->canTargetOtherHeroes())
	{
		std::cout << "2.Ally\n";
		++options;
	}

	int action = 0;
	while (!readValidInt(1, options, action))
	{
		std::cout << "Try again\n\n\n";
	}

	switch (action)
	{
	case 1: 
		targetEnemy(hero, room);
		break;
	case 2:
		targetAlly(hero, heroes);
		break;
	}
}

void DungeonState::targetEnemy(Hero* hero, Room* room)
{
	std::cout << "Choose enemy\n";
	size_t numberOfEnemies = room->getNumberOfEnemies();
	size_t numberOfAliveEnemies = 0;
	for (size_t i = 0; i < numberOfEnemies; ++i)
	{
		if (room->getEnemy(i)->getHP() > 0)
		{
			++numberOfAliveEnemies;
			std::cout << numberOfAliveEnemies << ". ";
			room->getEnemy(i)->printBasicInfo();
		}
	}
	int action = -1;

	while (!readValidInt(1, numberOfAliveEnemies, action))
	{
		std::cout << "Try again\n\n\n";
	}

	size_t find = 0;
	for (size_t i = 0; i < numberOfEnemies; ++i)
	{
		if (room->getEnemy(i)->getHP() > 0)
		{
			++find;
			if (find == action)
			{
				hero->attackEnemy(room->getEnemy(i));
				break;
			}
			
		}
	}
}

void DungeonState::targetAlly(Hero* hero, std::vector<Hero*>& heroes)
{
	std::cout << "Choose ally\n";
	size_t numberOfHeroes = heroes.size();
	size_t numberOfAliveHeroes = 0;
	for (size_t i = 0; i < numberOfHeroes; ++i)
	{
		if (heroes[i]->getHP() > 0)
		{
			++numberOfAliveHeroes;
			std::cout << numberOfAliveHeroes << ". ";
			heroes[i]->printBasicInfo();
		}
	}
	int action = -1;

	while (!readValidInt(1, numberOfAliveHeroes, action))
	{
		std::cout << "Try again\n\n\n";
	}

	size_t find = 0;
	for (size_t i = 0; i < numberOfHeroes; ++i)
	{
		if (heroes[i]->getHP() > 0)
		{
			++find;
			if (find == action)
			{
				size_t numberOfAbilities = hero->getNumberOfAbilites();
				if (numberOfAbilities <= 0)
				{
					std::cout << "Hero has no abilities\n";
					break;
				}
				std::cout << "Choose ability:\n";
				hero->printAbilities();
				int command = -1;
				while (!readValidInt(1, numberOfAbilities, command))
				{
					std::cout << "Try again\n\n\n";
				}
				
				if (hero->requiresATarget(command))
				{
					hero->useAbility(command, heroes[i]);
				}
				else
				{
					hero->useAbility(command);
				}
				
				break;
			}
		}
	}
}



void DungeonState::enemyTurn(std::vector<Hero*>& heroes, Enemy* enemy , size_t turn , size_t index)
{
	size_t numberOfHeroes = heroes.size();
	bool attacked = false;
	for (size_t i = 0; i < numberOfHeroes; ++i)
	{
		if (heroes[i]->getHP() > 0 && heroes[i]->mustBeAttacked())
		{
			enemy->attackHero(heroes[i]);
			attacked = true;
		}
	}

	if (!attacked)
	{
		size_t find = 0;
		while (true)
		{
			size_t toAttack = (turn + index + find) % numberOfHeroes;
			if (heroes[toAttack]->getHP() > 0)
			{
				enemy->attackHero(heroes[toAttack]);
				break;
			}
			++find;
		
		}
	}
}

void DungeonState::createRandomTurnOrder(std::vector<size_t>& indices , std::mt19937& gen)
{
	std::iota(indices.begin(), indices.end(), std::size_t{ 0 });
	std::shuffle(indices.begin(), indices.end(), gen);
}

Dungeon* DungeonState::loadDungeonData(const std::string& name)
{
	std::ifstream read(name, std::ios::binary);
	if (!read.is_open())
	{
		return nullptr;
	}
	Dungeon* ptr = nullptr;
	try
	{
		ptr = new Dungeon(read);
	}
	catch (...)
	{
		read.close();
		return nullptr;
	}
	read.close();
	return ptr;

}

std::vector<Hero*> DungeonState::loadHeroes(const std::vector<std::string>& heroesThatWillEnterDungeon)
{
	std::vector<Hero*> heroes;
	size_t allocated = 0;
	try
	{
		size_t numberOfHeroes = heroesThatWillEnterDungeon.size();
		heroes.resize(numberOfHeroes);
		for (size_t i = 0; i < numberOfHeroes; ++i)
		{
			heroes[i] = loadHeroData(heroesThatWillEnterDungeon[i]);
			if (!heroes[i])
			{
				std::cout << "Could not load heroes\n\n\n";
				throw std::runtime_error("Error");
			}
			++allocated;
		}
	}
	catch (...)
	{
		freeHeap(heroes, allocated);
		throw;
	}

	return heroes;
}

int DungeonState::display()
{
	return 1;
}
SystemState* DungeonState::execute(int action)
{
	changeState();
	return nullptr;
}


void DungeonState::freeHeap(std::vector<Hero*>& heroes, size_t allocated)
{
	for (size_t i = 0; i < allocated; ++i)
	{
		delete heroes[i];
		heroes[i] = nullptr;
	}
}


Hero* DungeonState::loadHeroData(const std::string& name)
{
	std::ifstream heroFile(name, std::ios::binary);
	if (!heroFile.is_open())
	{
		return nullptr;
	}

	uint32_t heroClassValue = 0;
	heroFile.read(reinterpret_cast<char*>(&heroClassValue), sizeof(heroClassValue));

	HeroClass type = static_cast<HeroClass>(heroClassValue);

	Hero* hero = HeroFactory::loadHeroFromFile(heroFile, type);
	if (!hero)
	{
		return nullptr;
	}
	heroFile.close();
	
	return hero;

}


bool DungeonState::updateAndSafeData(const Dungeon* dungeon, const std::vector<Hero*>& heroes , std::vector<std::string>& allHeroes)
{
	try
	{
		safeDungeonData(dungeon);
		updateAndSafeHeroData(heroes , allHeroes);
	}
	catch (...)
	{
		return false;
	}
	
	return true;
}

void DungeonState::updateAndSafeHeroData(const std::vector<Hero*>& heroes , std::vector<std::string>& allHeroes)
{
	size_t size = heroes.size();

	for (size_t i = 0; i < size; ++i)
	{
		if (heroes[i]->getHP() > 0)
		{
			std::ofstream store(heroes[i]->getName(), std::ios::binary);
			if (!store.is_open())
			{
				throw std::runtime_error("Error");
			}
			heroes[i]->writeToFile(store);
			store.close();
		}
		else
		{
			size_t numberOfHeroes = allHeroes.size();
			for (size_t j = 0; j < numberOfHeroes; ++j)
			{
				if (heroes[i]->getName() == allHeroes[j])
				{
					allHeroes.erase(allHeroes.begin() + j);
					break;
				}
			}

			std::remove(heroes[i]->getName().c_str());
		}
	}
	
}
void DungeonState::safeDungeonData(const Dungeon* dungeon)
{
	std::ofstream dungeonFile(dungeon->getNameOfDungeon(), std::ios::binary);
	if (!dungeonFile.is_open())
	{
		std::cout << "Critical error could not safe progress\n\n\n";
		throw std::runtime_error("Error");
	}
	try
	{
		dungeon->writeDataToFile(dungeonFile);
	}
	catch (...)
	{
		std::cout << "Critical error could not safe progress\n\n\n";
		dungeonFile.close();
		throw std::runtime_error("Error");
	}
	dungeonFile.close();

}