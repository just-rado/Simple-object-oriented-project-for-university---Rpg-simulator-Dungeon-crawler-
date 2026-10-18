#include "LoginState.h"
#include <fstream>
#include <iostream>
#include "StringFunctionsForFiles.h"
#include <vector>
#include "GameSelectState.h"

int LoginState::display()
{
	return 1;
}
std::string LoginState::loginPrompt()
{
	while (true)
	{
		std::string username = getString("username");
		
		std::ifstream account(username, std::ios::binary);
		if (!account.is_open())
		{
			if (!tryAgain("Error occurred"))
			{
				return std::string();
			}
			continue;
		}
		std::string password = readString(account);
		account.close();

		if (!account.good())
		{
			if (!tryAgain("Error occurred"))
			{
				return std::string();
			}
			continue;
		}
		
		while (true)
		{
			std::string inputPassword = getString("password");

			if (password != inputPassword)
			{
				if (!tryAgain("Incorrect password"))
				{
					return std::string();
				}
				continue;
			}
			return username;
		}
		
	}
}

SystemState* LoginState::execute(int action)
{
	changeState();
	std::string successfullyCreated = loginPrompt();
	if (successfullyCreated.empty())
	{
		return nullptr;
	}
	return new (std::nothrow) GameSelectState(successfullyCreated);
}