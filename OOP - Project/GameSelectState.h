#pragma once
#include "SystemState.h"
#include <string>
#include <vector>

class GameSelectState: public SystemState
{
public:
	GameSelectState(const std::string& nameOfAccount);

	int display()override;
	SystemState* execute(int action)override;

private:
	std::string nameOfAccount;
	std::string password;
	std::vector<std::string> nameOfGames;

	void printGames()const;

	void createNewGame();

	std::string selectGame()const;

	bool storeAccount()const;
};

