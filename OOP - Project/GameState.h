#pragma once
#include "SystemState.h"
#include "Hero.h"
#include <vector>
#include <string>
class GameState : public SystemState
{
public:

	int display()override;
	SystemState* execute(int action)override;



private:
	std::string nameOfGame;
	std::vector<std::string> namesOfHeroes;
	std::vector<std::string> nameOfDungeons;
	
	std::vector<Hero*> heroes;
	
	void addNewHero(const std::string& name, HeroClass heroClass);

	Hero* loadHeroData(const std::string& name);

	void heroInfo(const std::string& nameOfHero);

	void printNameOfHeroes()const;

	void manageItems(const std::string& firstHero, const std::string& secondHero);
	
	void dungeonInfo()const;

	void printNameOfDungeons()const;

	void selectHeroesToEnterDungeon();

	bool enterDungeon(const std::string& nameOfDungeon);
};

