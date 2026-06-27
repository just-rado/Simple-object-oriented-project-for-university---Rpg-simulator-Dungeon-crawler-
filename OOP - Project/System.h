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
	std::string userName;
	std::string password;
	std::vector<std::string> nameOfGames;
	Game* currentGame;

	

	

};


