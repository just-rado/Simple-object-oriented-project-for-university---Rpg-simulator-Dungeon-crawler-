#pragma once
#include "SystemState.h"
#include <string>
#include <vector>
class GameSelectState: public SystemState
{
public:

	int display()override;
	SystemState* execute(int action)override;

private:
	std::vector<std::string> nameOfGames;

	void printGames()const;

	bool createNewGame();
};

