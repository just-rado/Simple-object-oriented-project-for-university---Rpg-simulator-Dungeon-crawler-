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

	// rule of three

private:
	// divide the different actions into different states , e.g adding newHero / inventory state / dungeon selection state and so on
	std::string nameOfGame;
	std::vector<std::string> namesOfHeroes;
	std::vector<std::string> nameOfDungeons;
	
	static bool isBlank(const std::string& string);

	/*bool isHeroAlreadyLoaded(const std::string& name)const;*/

	bool doesHeroExist(const std::string& name)const;

	std::string inputNewHeroName()const;

	void addNewHero();

	//Hero* getLoadedHero(const std::string& name)const;

	void printNameOfHeroes()const;

	void manageItemsBetweenTwoHeroes(const Hero* firstHero, const Hero* secondHero);

	void manageItemsOfASingleHero(const Hero* hero);

	//void manageItems();
	
	void dungeonInfo()const;

	void printNameOfDungeons()const;

	void selectHeroesToEnterDungeon();

	bool enterDungeon(const std::string& nameOfDungeon);
};

