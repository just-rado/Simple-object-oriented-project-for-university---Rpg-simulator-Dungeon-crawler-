#include "GameSelectState.h"
#include "StringFunctionsForFiles.h"
#include <string>
#include <vector>
#include <iostream>
#include "SafeInputReading.h"
#include "StringHelpers.h"
#include "GameState.h"
#include <fstream>
#include <stdexcept>


GameSelectState::GameSelectState(const std::string& nameOfAccount)
{
	std::ifstream account(nameOfAccount, std::ios::binary);
	if (!account.is_open())
	{
		throw std::exception();
	}

	this->password = readString(account);

	this->nameOfAccount = nameOfAccount;

	uint32_t numberOfGames = 0;
	account.read(reinterpret_cast<char*>(&numberOfGames), sizeof(numberOfGames));

	this->nameOfGames.resize(numberOfGames);
	
	for (uint32_t i = 0; i < numberOfGames; ++i)
	{
		if (!account.good())
		{
			account.close();
			throw std::exception();
		}
		this->nameOfGames[i] = readString(account);
	}
	account.close();
}

bool GameSelectState::storeAccount()const
{
	std::ofstream storeAccount(this->nameOfAccount, std::ios::binary);
	if (!storeAccount.is_open())
	{
		std::cout << "Critical error could not save progress\n";
		return false;
	}

	writeString(storeAccount, this->password);

	uint32_t numberOfGames = static_cast<uint32_t>(this->nameOfGames.size());
	storeAccount.write(reinterpret_cast<const char*>(&numberOfGames), sizeof(numberOfGames));

	for (uint32_t i = 0; i < numberOfGames; ++i)
	{
		if (!storeAccount)
		{
			std::cout << "Error occurred. Could not save everything\n";
			return false;
		}
		writeString(storeAccount, this->nameOfGames[i]);
	}

	return true;
}
int GameSelectState::display()
{
	while (true)
	{
		std::cout << "Choose option:\n";
		std::cout << "1.Create new game\n";
		std::cout << "2.Load game\n";
		std::cout << "3.Show all games\n";
		std::cout << "4.Save and quit\n";

		int action = 0;
		
		if (!readValidInt(1, 4, action))
		{
			if (!tryAgain("Invalid input"))
			{
				return 4;
			}
			else
			{
				continue;
			}
		}

		switch (action)
		{
		case 1:
			createNewGame();
			continue;
		case 2:
			return 2;
		case 3: 
			printGames();
			continue;
		case 4:
			return 4;
		}
		
	}
} 
SystemState* GameSelectState::execute(int action)
{
	switch (action)
	{
	case 2:
	{
		std::string selectedGame = selectGame();
		if (selectedGame.empty())
		{
			return nullptr;
		}
		return new (std::nothrow) GameState(selectedGame);
	}
	case 4:
		if (!storeAccount())
		{
			if (!tryAgain("Error occurred while saving data"))
			{
				changeState();
			}
		}
		else
		{
			changeState();
		}
		
		return nullptr;
	}
}

void GameSelectState::printGames()const
{
	size_t size = this->nameOfGames.size();
	if (size == 0)
	{
		std::cout << "No games" << "\n\n\n";
		return;
	}
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << this->nameOfGames[i] << '\n';
	}
	std::cout << "\n\n\n";
}


void GameSelectState::createNewGame()
{
	while (true)
	{
		std::string nameOfGame = getString("name");

		if (!isNameValid(nameOfGame))
		{
			if (tryAgain("Invalid name"))
			{
				continue;
			}
			else
			{
				return;
			}
		}
		
		bool errorOccurred = false;

		for (size_t i = 0; i < nameOfGames.size(); ++i)
		{
			if (areEqual(nameOfGame , nameOfGames[i]))
			{
				errorOccurred = true;
				if (!tryAgain("Game with this name already exists"))
				{
					return;
				}
				break;
			}
		}

		if (errorOccurred)
		{
			continue;
		}

		this->nameOfGames.push_back(nameOfGame);

		return;
	}
}

std::string GameSelectState::selectGame()const
{
	std::string newGame;
	while (true)
	{
		printGames();
		newGame = getString("which game to play");

		if (!doesStringExist(newGame , this->nameOfGames))
		{
			if (tryAgain("No game with that name exists"))
			{
				continue;
			}
			else
			{
				newGame.clear();
				return newGame;
			}
		}

		return newGame;
	}
}