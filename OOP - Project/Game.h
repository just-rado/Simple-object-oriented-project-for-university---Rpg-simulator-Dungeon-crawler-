#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Hero.h"
#include "Dungeon.h"

class Game
{
public:

	Game(std::ifstream& read);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	~Game();

	void loadHeroData(size_t index);
	void loadDungeon(size_t index);

	void addNewHero(std::string name, HeroClass heroClass);
	void addNewDungeon(std::string name);

	void storeGame(std::ofstream& write)const;

	
private:
	std::string nameOfGame;

	std::vector<std::string> namesOfHeroes;
	
	std::vector<std::string> nameOfDungeons;


	std::vector<Hero*> heroes;
	Dungeon* currentDungeon;

	
};

