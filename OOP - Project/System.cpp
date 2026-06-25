#include "System.h"
#include "StringFunctionsForFiles.h"
#include <iostream>
#include <fstream>

System::System()
{
	this->currentGame = nullptr;
	while (true)
	{
		int option = 0;
		std::cout << "Choose option:\n" << "1. Login:\n" << "2. Register:\n";
		std::cin >> option;

		if (option == 1)
		{
			while (true)
			{
				std::string user;
				std::cout << "Enter username: ";
				std::cin >> user;
				if (isNameValid(user))
				{
					std::ifstream account(user, std::ios::binary);
					if (!account.is_open())
					{
						std::cout << "No account with this username exists\n" << "Try again\n";
						continue;
					}

					std::string actualPassword = readString(account);

					std::string password;
					std::cout << "Enter password: ";
					std::cin >> password;
					
					if (password != actualPassword)
					{
						std::cout << "Wrong password.\n" << "Try again\n";
						continue;
					}

					uint32_t numberOfGames = 0;
					account.read(reinterpret_cast<char*>(&numberOfGames), sizeof(numberOfGames));

					this->nameOfGames.resize(numberOfGames);
					if (numberOfGames == 0)
					{
						std::cout << "Successfully logged in account. There are no current games\n";
						break;
					}
					for (uint32_t i = 0; i < numberOfGames; ++i)
					{
						this->nameOfGames[i] = readString(account);
					}
					account.close();

					std::cout << "Successfully logged in account. Current games:\n";
					for (size_t i = 0; i < this->nameOfGames.size(); ++i)
					{
						std::cout << this->nameOfGames[i] << '\n';
					}

					std::cout << std::endl;
					break;

				}
				else
				{
					std::cout << "Invalid username . Try again\n";
				}
			}
			break;
			
		}
		else if (option == 2)
		{
			while (true)
			{
				std::string user;
				std::cout << "Enter new username: ";
				std::cin >> user;

				if (isNameValid(user))
				{
					std::ifstream check(user, std::ios::binary);
					if (check.is_open())
					{
						std::cout << "Account with that username already exists. Try again\n";
						continue;
					}

					std::string password;
					std::cout << "Enter passwor: ";
					std::cin >> password;

					std::ofstream newAccount(user, std::ios::binary);
					if (!newAccount.is_open())
					{
						std::cout << "Unable to create account\n";
						throw std::runtime_error("Error");
					}

					writeString(newAccount, password);

					newAccount.close();
					std::cout << "Account successfully created.\n";
					break;
					
				}
				

			
			}
			break;
		}
		else
		{
			std::cout << "Please choose between 1 and 2\n";
			continue;
		}
	}
	
}


void System::gameManage()
{
	while (true)
	{
		std::cout << "Chose option:\n" << "1.Create new game\n" << "2.Load game\n" << "3.Save current game\n" << "4.See all create games\n";
		int option = 0;
		std::cin >> option;

		if (option == 1)
		{
			while(true)
			{
				std::string nameOfGame;
				std::cout << "Give a name for the new game";
				std::cin >> nameOfGame;
				if (!isNameValid(nameOfGame))
				{
					std::cout << "Invalid name. Try again\n";
					continue;
				}
				bool flagSet = false;
				for (size_t i = 0; i < nameOfGames.size(); ++i)
				{
					if (nameOfGame == nameOfGames[i])
					{
						flagSet = true;
						std::cout << "Name already taken. Try again\n";
						break;
					}
				}
				if (flagSet)
				{
					continue;
				}
				this->nameOfGames.push_back(nameOfGame);
				heroManage();
				break;

			}
			
		}
		else if (option == 2)
		{
			std::cout << "Chose which game to load:\n";
			if (this->nameOfGames.size() == 0)
			{
				std::cout << "No games exist\n";
				break;
			}

			std::cout << "Games are:\n";
			for (size_t i = 0; i < this->nameOfGames.size(); ++i)
			{
				std::cout << this->nameOfGames[i] << '\n';
			}

			std::string nameOfGame;
			std::cin >> nameOfGame;
			bool foundGame = false;
			for (size_t i = 0; i < this->nameOfGames.size(); ++i)
			{
				if (nameOfGame == this->nameOfGames[i])
				{
					std::ifstream current(nameOfGame, std::ios::binary);
					if (!current.is_open())
					{
						throw std::runtime_error("Error");
					}

					delete this->currentGame;

					this->currentGame = new Game(current);
					foundGame = true;
					break;
				}
			}
			if (foundGame)
			{
				break;
			}

		}
		break;
	}
	

	

}

bool System::isNameValid(const std::string& name)const
{
	if (name.empty())
	{
		return false;
	}

	for (char c : name)
	{
		if (!std::isalnum(static_cast<unsigned char>(c)) && c != '_' && c != '-')
		{
			return false;
		}
	}
	return true;
}

void System::heroManage()
{

}