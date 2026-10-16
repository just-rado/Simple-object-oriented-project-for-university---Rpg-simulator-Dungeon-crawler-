#pragma once
#include <string>
#include <vector>

bool areEqual(const std::string& lhs, const std::string& rhs)
{
	size_t lhsSize = lhs.size();
	if (lhsSize != rhs.size())
	{
		return false;
	}

	for (size_t i = 0; i < lhsSize; ++i)
	{
		if (std::tolower(static_cast<unsigned char>(lhs[i])) != std::tolower(static_cast<unsigned char>(rhs[i])))
		{
			return false;
		}
	}

	return true;
}

bool doesStringExist(const std::string& string, const std::vector<std::string>& strings)
{
	size_t size = strings.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (areEqual(string, strings[i]))
		{
			return true;
		}
	}
	return false;
}