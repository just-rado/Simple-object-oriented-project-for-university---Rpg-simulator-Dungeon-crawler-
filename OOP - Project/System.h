#pragma once
#include <string>
#include <vector>
#include "Game.h"
class System
{
public:
	System();
	void gameManage();


private:
	std::vector<std::string> nameOfGames;
	Game* currentGame;

	void heroManage();

	bool isNameValid(const std::string& name)const;

};


