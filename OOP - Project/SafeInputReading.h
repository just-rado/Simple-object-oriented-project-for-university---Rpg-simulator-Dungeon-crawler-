#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

inline bool readValidInt(int min, int max , int& result)
{
	std::string line;
	if (!std::getline(std::cin, line))
	{
		throw std::runtime_error("Input close");
	}

	try
	{
		size_t pos = 0;
		int value = std::stoi(line, &pos);
		if (pos == line.size() && value >= min && value <= max)
		{
			result = value;
			return true;
		}
	}
	catch (...)
	{}

	return false;
}
