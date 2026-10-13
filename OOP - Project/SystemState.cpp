#include "SystemState.h"
#include <string>
#include <iostream>
#include <stdexcept>
#include "SafeInputReading.h"

bool SystemState::tryAgain(const std::string& error)
{
	int action = 0;
	std::cout << error << '\n';
	std::cout << "Press 1 to try again\n";
	std::cout << "Press any other key to go back\n";
	
	if (readValidInt(1, 1, action))
	{
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

	if (!std::getline(std::cin, str))
	{
		throw std::runtime_error("Input close");
	}

	return str;
}