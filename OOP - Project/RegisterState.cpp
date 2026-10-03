#include "RegisterState.h"
#include <iostream>
#include "StringFunctionsForFiles.h"
#include <fstream>
int RegisterState::display()
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
				return 2;
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
				return 2;
			}
		}
		
		return 1;
	}
}
SystemState* RegisterState::execute(int action)
{
	if (action == 1)
	{

	}
	else
	{
		return nullptr;
	}
}

bool RegisterState::doesAccountAlreadyExist(const std::string& userName)
{
	std::ifstream check(userName, std::ios::binary);
	if (check.is_open())
	{
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

