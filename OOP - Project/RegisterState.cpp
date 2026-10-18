#include "RegisterState.h"
#include <iostream>
#include "StringFunctionsForFiles.h"
#include <fstream>
#include "GameSelectState.h"
int RegisterState::display()
{
	return 1;
}

std::string RegisterState::regPrompt()
{
	while (true)
	{
		std::string username = getString("username");
		
		if (doesAccountAlreadyExist(username))
		{
			if (tryAgain("An account with this username already exists"))
			{
				continue;
			}
			else
			{
				return std::string();
			}
		}

		std::string password = getString("password");

		if (!createAccount(username, password))
		{
			if (tryAgain("Unable to create account"))
			{
				continue;
			}
			else
			{
				return std::string();
			}
		}

		return username;
	}
}

SystemState* RegisterState::execute(int action)
{
	std::string successfullyCreated = regPrompt();
	changeState();

	if (successfullyCreated.empty())
	{
		return nullptr;
	}
	
	return new (std::nothrow) GameSelectState(successfullyCreated);
}

bool RegisterState::doesAccountAlreadyExist(const std::string& userName)
{
	std::ifstream check(userName, std::ios::binary);
	if (check.is_open())
	{
		check.close();
		return true;
	}

	return false;
}



bool RegisterState::createAccount(const std::string& userName, const std::string& password)
{
	std::ofstream newAccount(userName , std::ios::binary);
	if (!newAccount.is_open())
	{
		return false;
	}

	writeString(newAccount, password);

	uint32_t initialNumberOfGames = 0;
	newAccount.write(reinterpret_cast<const char*>(&initialNumberOfGames), sizeof(initialNumberOfGames));

	newAccount.close();

	std::cout << "Account successfully created.\n\n\n";

	return true;
}

