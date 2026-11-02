#pragma once
#include "SystemState.h"
#include "Dungeon.h"
#include <string>
#include <vector>
#include "Hero.h"
class DungeonState: public SystemState
{
public:
	int display() override;
	SystemState* execute(int action)override;

	DungeonState(const std::string& dungeonName , const std::vector<std::string>& heroesThatWillEnterDungeon,
		std::vector<std::string>& allHeroes);
	



private:

	static void freeHeap(std::vector<Hero*>& heroes, size_t allocated);

	static Dungeon* loadDungeonData(const std::string& name);
	static std::vector<Hero*> loadHeroes(const std::vector<std::string>& heroesThatWillEnterDungeon);
	static Hero* loadHeroData(const std::string& name);

	static bool updateAndSafeData(const Dungeon* dungeon , const std::vector<Hero*>& heroes , std::vector<std::string>& allHeroes);
	static void updateAndSafeHeroData(const std::vector<Hero*>& heroes , std::vector<std::string>& allHeroes);
	static void safeDungeonData(const Dungeon* dungeon);

	static void enterDungeon(std::vector<Hero*>& heroes, Dungeon* dungeon);
	static void enterRoom(std::vector<Hero*>& heroes, Room* room , bool& allHeroesDied);
	static void playTurn(std::vector<Hero*>& heroes, const std::vector<size_t>& heroIndices, const std::vector<size_t>& enemyIndices, 
		Room* room , size_t turn , bool& allHeroesDied , bool& allEnemiesDied);
	static void heroTurn(std::vector<Hero*>& heroes, Hero* hero , Room* room);
	static void enemyTurn(std::vector<Hero*>& heroes , Enemy* enemy , size_t turn , size_t index);
	static void targetEnemy(Hero* hero , Room* room);
	static void targetAlly(Hero* hero, std::vector<Hero*>& heroes);
	static void createRandomTurnOrder(std::vector<size_t>& indices , std::mt19937& gen);

};

