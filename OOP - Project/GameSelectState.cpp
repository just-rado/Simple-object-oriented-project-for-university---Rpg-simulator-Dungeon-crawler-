#include "GameSelectState.h"
#include "StringFunctionsForFiles.h"
#include <string>
#include <vector>
#include <iostream>

int GameSelectState::display()
{
	while (true)
	{
		std::cout << "Choose option:" << '\n';
		std::cout << "1.Create new game" << '\n';
		std::cout << "2.Load game" << '\n';
		std::cout << "3.Show all games" << '\n';
		std::cout << "4.Save and quit" << '\n';

		int action = 0;
		std::cin >> action;

		if (action == 1)
		{
			createNewGame();
			continue;
		}
		else if(action == 2)
		{
			return 2;
		}
		else if(action == 3)
		{
			printGames();
			continue;
		}
		else if (action == 4)
		{
			return 4;
		}
		else
		{
			std::cout << "Please enter a valid option";
			std::cout << "\n\n\n";
			continue;
		}
	}
}
SystemState* GameSelectState::execute(int action)
{
	return nullptr;
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


bool GameSelectState::createNewGame()
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
				return false;
			}
		}
		
		bool errorOccurred = false;

		for (size_t i = 0; i < nameOfGames.size(); ++i)
		{
			if (nameOfGame == nameOfGames[i])
			{
				errorOccurred = true;
				if (!tryAgain("Game with this name already exists"))
				{
					return false;
				}
				break;
			}
		}

		if (errorOccurred)
		{
			continue;
		}

		this->nameOfGames.push_back(nameOfGame);

		return true;
	}
}