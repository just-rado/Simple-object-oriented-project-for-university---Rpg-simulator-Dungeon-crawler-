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
						break;
					}

					
					this->password = readString(account);

					while (true)
					{
						std::string password;
						std::cout << "Enter password: ";
						std::cin >> password;
						if (password != this->password)
						{
							std::cout << "Wrong password.\n" << "Try again\n";
							continue;
						}
						break;
					}
					this->userName = user;
					
					uint32_t numberOfGames = 0;
					account.read(reinterpret_cast<char*>(&numberOfGames), sizeof(numberOfGames));

					this->nameOfGames.resize(numberOfGames);
					if (numberOfGames == 0)
					{
						account.close();
						break;
					}
					for (uint32_t i = 0; i < numberOfGames; ++i)
					{
						this->nameOfGames[i] = readString(account);
					}
					account.close();
					std::cout << std::endl;
					break;

				}
				else
				{
					std::cout << "Invalid username. Try again\n";
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
					std::cout << "Enter password: ";
					std::cin >> password;

					std::ofstream newAccount(user, std::ios::binary);
					if (!newAccount.is_open())
					{
						std::cout << "Unable to create account\n";
						throw std::runtime_error("Error");
					}

					this->userName = user;
					this->password = password;

					writeString(newAccount , this->password);

					uint32_t initiaNumberOfGames = 0;
					newAccount.write(reinterpret_cast<const char*>(&initiaNumberOfGames), sizeof(initiaNumberOfGames));

					newAccount.close();
					std::cout << "Account successfully created.\n";
					break;
					
				}
				else
				{
					std::cout << "Name is invalid. Try again\n";
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
	gameManage();
}


void System::gameManage()
{
	while (true)
	{
		std::cout << "Chose option:\n" << "1.Create new game\n" << "2.Load game\n" << "3.See all created games\n" <<"4.Quit\n";
		int option = 0;
		std::cin >> option;

		if (option == 1)
		{
			while(true)
			{
				std::string nameOfGame;
				std::cout << "Enter a name for  new game: ";
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

				this->currentGame = new Game(nameOfGame);
				break;
			
			}
			
		}
		else if (option == 2)
		{
			std::cout << "Choose which game to load:\n";
			if (this->nameOfGames.size() == 0)
			{
				std::cout << "No games exist\n";
				continue;
			}

			std::cout << "Games are:\n";
			for (size_t i = 0; i < this->nameOfGames.size(); ++i)
			{
				std::cout << i + 1 << ". " << this->nameOfGames[i] << '\n';
			}

		
			bool foundGame = false;
			while (!foundGame)
			{
				std::cout << "Choose game:";
				int game = 0;
				std::cin >> game;

				if (game < 1 || game > this->nameOfGames.size())
				{
					continue;
				}

				std::ifstream current(this->nameOfGames[game - 1], std::ios::binary);
				if (!current.is_open())
				{
					std::cout << "Could not open game\n";
					std::cout << "Do you wish to try again.\n" << "1.Yes\n" << "2.No";
					int exit = 0;
					std::cin >> exit;
					if (exit == 2)
					{
						foundGame = true;
					}
					continue;
				}

				delete this->currentGame;
				this->currentGame = new Game(current);

				foundGame = true;
						
			}

		}
		else if (option == 3)
		{
			size_t size = this->nameOfGames.size();
			if (size == 0)
			{
				std::cout << "No games\n";
				continue;
			}
			for (size_t i = 0; i < size; ++i)
			{
				std::cout << this->nameOfGames[i] << '\n';
			}
		}
		else if (option == 4)
		{
			std::ofstream storeAccount(this->userName , std::ios::binary);

			writeString(storeAccount, this->password);

			uint32_t numberOfGames = static_cast<uint32_t>(this->nameOfGames.size());
			storeAccount.write(reinterpret_cast<const char*>(&numberOfGames), sizeof(numberOfGames));

			for (uint32_t i = 0; i < numberOfGames; ++i)
			{
				writeString(storeAccount, this->nameOfGames[i]);
			}
			break;
		}
		
	}
	

	

}


