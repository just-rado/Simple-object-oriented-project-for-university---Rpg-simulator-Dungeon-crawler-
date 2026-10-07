#include "SystemState.h"
#include <string>
#include <iostream>

bool SystemState::tryAgain(const std::string& error)
{
	int action = 0;
	std::cout << error << '\n';
	std::cout << "Press 1 to try again\n";
	std::cout << "Press any other key to go back\n";
	std::cin >> action;
	if (action == 1)
	{
		std::cout << "\n\n\n\n\n";
		return true;

	}
	else
	{
		return false;
	}
}

std::string SystemState::getString(const std::string& output)
{
	std::string str;
	std::cout << "Enter " << output << ": ";
	std::getline(std::cin, str);
	return str;
}