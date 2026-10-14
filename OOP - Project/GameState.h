#pragma once
#include "SystemState.h"
#include <vector>
#include <string>
#include "Dungeon.h"
class GameState : public SystemState
{
public:

	int display()override;
	SystemState* execute(int action)override;

private:
	// divide the different actions into different states , e.g adding/removing hero / inventory state / dungeon selection state and so on
	std::string nameOfGame;
	std::vector<std::string> namesOfHeroes;
	std::vector<std::string> nameOfDungeons;

	/*bool isHeroAlreadyLoaded(const std::string& name)const;*/

	//Hero* getLoadedHero(const std::string& name)const;

	void printNameOfHeroes()const;
	
	void dungeonInfo()const;

	void printNameOfDungeons()const;

	void selectHeroesToEnterDungeon();

	bool enterDungeon(const std::string& nameOfDungeon);

	static void printStrings(const std::vector<std::string>& strings);

	Dungeon* loadDungeon(const std::string& nameOfDungeon)const;
};

