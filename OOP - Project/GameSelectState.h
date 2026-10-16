#pragma once
#include "SystemState.h"
#include <string>
#include <vector>
#include <fstream>
class GameSelectState: public SystemState
{
public:
	GameSelectState() = default;
	GameSelectState(const std::string& nameOfFile);

	int display()override;
	SystemState* execute(int action)override;

private:
	std::string nameOfAccount;
	std::vector<std::string> nameOfGames;

	void printGames()const;

	bool createNewGame();

	std::string loadGame()const;
};

