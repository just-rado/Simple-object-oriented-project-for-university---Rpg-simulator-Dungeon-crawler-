#include "Dungeon.h"
#include "StringFunctionsForFiles.h"
#include <iostream>

Dungeon::Dungeon(const std::string& name , const Room* room): name(name) ,position() ,currentRoom(nullptr)
{
	if (!room)
	{
		throw std::invalid_argument("Error");
	}
	this->currentRoom = new Room(*room);
}


Dungeon::Dungeon(std::ifstream& read)
{
	this->currentRoom = nullptr;
	this->name = readString(read);

	bool roomExists = false;
	read.read(reinterpret_cast<char*>(&roomExists), sizeof(roomExists));

	if (roomExists)
	{
		this->currentRoom = new Room(read);
	}
	this->position = read.tellg();
	
	if (!read)
	{
		throw std::runtime_error("Error");
	}
}



Dungeon::Dungeon(const Dungeon& other)
{
	this->name = other.name;
	this->position = other.position;
	this->currentRoom = new Room(*other.currentRoom);
}
Dungeon& Dungeon::operator=(const Dungeon& other)
{
	if (this != &other)
	{
		std::string newName = other.name;

		Room* newRoom = new Room(*other.currentRoom);
		
		delete this->currentRoom;
		this->currentRoom = newRoom;

		this->name = std::move(newName);
		position = other.position;
	}
	return *this;
}
Dungeon::~Dungeon()
{
	delete this->currentRoom;
	this->currentRoom = nullptr;
}

void Dungeon::writeNameToFile(std::ofstream& write)const
{
	writeString(write, this->name);
	if (!write)
	{
		throw std::runtime_error("Error");
	}
}

void Dungeon::writeCurrentRoomToFile(std::ofstream& write)const
{
	bool exists = (this->currentRoom != nullptr);
	write.write(reinterpret_cast<const char*>(&exists), sizeof(exists));

	if (exists)
	{
		this->currentRoom->writeToFile(write);
	}

	if (!write)
	{
		throw std::runtime_error("Error");
	}
}

bool Dungeon::loadNextRoom(std::ifstream& file)
{
	file.seekg(position);

	bool roomExists = false;
	file.read(reinterpret_cast<char*>(&roomExists), sizeof(roomExists));

	if (roomExists)
	{
		Room* newRoom = new Room(file);
		
		delete this->currentRoom;
		this->currentRoom = newRoom;
		
		this->position = file.tellg();
	}
	else
	{
		this->currentRoom = nullptr;
		this->position = file.tellg();
		
		return false;
	}
	

	if (!file)
	{
		
		return false;
	}
	
	return true;
}

const std::string& Dungeon::getNameOfDungeon()const
{
	return this->name;
}
const Room* Dungeon::getCurrentRoom()const
{
	return this->currentRoom;
}

void Dungeon::enter(std::vector<Hero*>& heroes)
{
	
	if (!this->currentRoom)
	{
		return;
	}

	std::cout << "\n\n\n";

	for (size_t i = 0; i < 10; ++i)
	{
		std::cout << '\n';
	}
	
	while (this->currentRoom)
	{
		std::cout << std::endl;
		std::cout << "Entering room\n";
		std::cout << this->currentRoom->getNameOfroom() << '\n' << '\n';
		std::cout << "Combat started:\n";
		bool allEnemiesDefeated = false;
		bool allHeroesAreDefeated = false;
		size_t turn = 1;
		while (!allEnemiesDefeated || !allHeroesAreDefeated)
		{
			std::cout << "Turn: " << turn << "\n\n\n";


			size_t numberOfAcTions = std::min(heroes.size(), this->currentRoom->getNumberOfEnemies());
			std::vector<bool> hasActed(heroes.size(), false);
			for (size_t i = 0; i < numberOfAcTions; ++i)
			{
				size_t currentEnemy = 0;
				std::cout << "Your turn:\n" << "Select hero\n";


				for (size_t k = 0; k < heroes.size(); ++k)
				{
					if (!hasActed[k] && heroes[k])
					{
						std::cout << k + 1 << ". " << heroes[k]->getName() << "      ";
						printHeroClass(heroes[k]->getClass());

					}
				}

				int hero = 0;
				while (true)
				{
					std::cin >> hero;
					if (hero < 1 || hero > heroes.size() || hasActed[hero - 1])
					{
						std::cout << "Select a valid hero\n\n";
						continue;
					}
					break;
				}

				int target = 0;
				while (true)
				{
					std::cout << "Select target:\n";
					std::cout << "1.Ally\n" << "2.Enemy\n";
					std::cin >> target;
					if (target < 1 || target > 2)
					{
						continue;
					}
					break;
				}

				if (target == 1)
				{
					std::cout << "Select ally\n";
					for (size_t j = 0; j < heroes.size(); ++j)
					{
						if (heroes[j] && heroes[j]->getHP() > 0)
						{
							std::cout << j + 1 << ". " << heroes[j]->getName() << '\n';
						}
					}
					while (true)
					{
						std::cin >> target;
						if (target < 1 || target > heroes.size())
						{
							std::cout << "Select valid hero\n";
							continue;
						}
						else if (!heroes[target])
						{
							std::cout << "Select valid hero\n";
							continue;
						}
						else if (heroes[target] && heroes[target]->getHP() <= 0)
						{
							std::cout << "Select valid hero\n";
							continue;
						}
						break;
					}
					heroes[hero - 1]->useAbility(1, heroes[target]);

				}
				else if (target == 2)
				{
					std::cout << "Select enemy\n";
					for (size_t j = 0; j < this->currentRoom->getNumberOfEnemies(); ++j)
					{
						if (this->currentRoom->getEnemy(j)->getHP() > 0)
						{
							std::cout << j + 1 << ". " << this->currentRoom->getEnemy(j)->getName() << '\n';
						}
					}
					while (true)
					{
						std::cin >> target;
						if (target < 1 || target > this->currentRoom->getNumberOfEnemies())
						{
							std::cout << "Select valid enemy\n";
							continue;
						}
						else if (this->currentRoom->getEnemy(target - 1)->getHP() <= 0)
						{
							std::cout << "Select valid enemy\n";
							continue;
						}
						break;
					}
					int action = 0;
					while (true)
					{

						std::cout << "Select action:\n" << "1.Attack enemy\n" << "2.Use hero ability\n";
						std::cin >> action;
						if (action != 1 && action != 2)
						{
							std::cout << "Select valid action\n";
							continue;
						}
						break;
					}
					if (action == 1)
					{
						heroes[hero - 1]->attackEnemy(this->currentRoom->getEnemy(target - 1));
					}
					else if (action == 2)
					{
						heroes[hero - 1]->useAbility(1, this->currentRoom->getEnemy(target - 1));
					}

				}
				hasActed[hero - 1] = true;

				while (true)
				{
					if (currentEnemy >= this->currentRoom->getNumberOfEnemies())
					{
						allEnemiesDefeated = true;
						break;
					}
					if (this->currentRoom->getEnemy(currentEnemy)->getHP() <= 0)
					{
						++currentEnemy;
						continue;
					}
					break;
				}
				if (allEnemiesDefeated)
				{
					break;
				}


				int indexOfHeroToAttack = -1;
				for (size_t i = 0; i < heroes.size(); ++i)
				{
					if (heroes[i] && heroes[i]->getHP() > 0)
					{
						indexOfHeroToAttack = i;
						break;
					}
				}
				if (indexOfHeroToAttack < 0)
				{
					std::cout << "All heroes are dead\n\n";
					allHeroesAreDefeated = true;
					break;
				}

				for (size_t i = indexOfHeroToAttack; i < heroes.size(); ++i)
				{
					if (heroes[i] && heroes[i]->getHP() > 0 && heroes[i]->calculatePriority() < heroes[indexOfHeroToAttack]->calculatePriority())
					{
						indexOfHeroToAttack = i;
					}
				}

				this->currentRoom->getEnemy(currentEnemy)->attackHero(heroes[indexOfHeroToAttack]);

				std::cout << "Hero info:\n\n";
				for (size_t i = 0; i < heroes.size(); ++i)
				{
					if (heroes[i])
					{
						std::cout << "MAX_HP: " << heroes[i]->getMaxHP() << "    Current Hp: " << heroes[i]->getHP() << '\n';
					}
				}

				std::cout << "Enemy info:\n\n";
				for (size_t i = 0; i < this->getCurrentRoom()->getNumberOfEnemies(); ++i)
				{
					if (this->getCurrentRoom()->getEnemy(i))
					{
						std::cout << this->getCurrentRoom()->getEnemy(i)->getHP() << '\n';
					}
				}


			}
			for (size_t i = 0; i < heroes.size(); ++i)
			{
				if (heroes[i] && heroes[i]->getHP() > 0)
				{
					heroes[i]->updateStatusOfCharacter();
				}
			}

			for (size_t i = 0; i < this->getCurrentRoom()->getNumberOfEnemies(); ++i)
			{
				if (this->getCurrentRoom()->getEnemy(i) && this->getCurrentRoom()->getEnemy(i)->getHP() > 0)
				{
					this->getCurrentRoom()->getEnemy(i)->updateStatusOfCharacter();
				}
			}
			++turn;
			if (turn == 2)
			{
				break;
			}
		}
		std::cout << "Do you wish to leave dungeon:\n";
		std::cout << "1.Yes\n" << "2.No\n";

		while (true)
		{
			int check = 2;
			std::cin >> check;
			if (check == 1)
			{
				return;
			}
			else if (check == 2)
			{
				break;
			}
			else
			{
				std::cout << "1.Yes or 2.No\n\n\n";
			}
		}
		std::ifstream loadNext(this->name, std::ios::binary);
		if (!loadNext.is_open())
		{
			std::cout << "Problem occured while trying to enter next room";
		}
		loadNextRoom(loadNext);
		loadNext.close();
	}
	
}