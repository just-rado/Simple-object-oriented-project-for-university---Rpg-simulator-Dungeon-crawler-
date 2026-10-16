#pragma once
#include "SystemState.h"
#include <vector>
#include <string>
#include "Dungeon.h"
class GameState : public SystemState
{
public:
	GameState(const std::string& nameOfGame);
	int display()override;
	SystemState* execute(int action)override;

private:
	std::string nameOfGame;
	std::vector<std::string> namesOfHeroes;
	std::vector<std::string> nameOfDungeons;
	std::vector<std::string> nameOfCompletedDungeons;

	/*bool isHeroAlreadyLoaded(const std::string& name)const;*/

	//Hero* getLoadedHero(const std::string& name)const;

	void printNameOfHeroes()const;
	
	void dungeonInfo()const;

	void printNameOfDungeons()const;

	void printNameOfCompletedDungeons()const;

	std::vector<std::string> selectHeroesToEnterDungeon();

	const std::string& selectDungeonToEnter();

	static void printStrings(const std::vector<std::string>& strings);

	Dungeon* loadDungeon(const std::string& nameOfDungeon)const;
};

