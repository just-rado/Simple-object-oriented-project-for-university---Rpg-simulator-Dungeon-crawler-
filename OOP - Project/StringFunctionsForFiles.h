#pragma once
#include <string>
#include <vector>
#include <fstream>

inline std::string readString(std::ifstream& file)
{
	uint32_t len = 0;

	file.read(reinterpret_cast<char*>(&len), sizeof(len));
	
	if (len == 0)
	{
		return "";
	}

	std::string result(len, '\0');


	file.read(&result[0], len);

	if (!file)
	{
		throw std::runtime_error("Failed to load string from file");
	}

	return result;
}

inline void writeString(std::ofstream& file, const std::string& string)
{
	uint32_t lenOfName = static_cast<uint32_t>(string.size());
	file.write(reinterpret_cast<const char*>(&lenOfName), sizeof(lenOfName));
	file.write(string.data(), lenOfName);

	if (!file)
	{
		throw std::runtime_error("Failed writing string");
	}
}

inline bool isNameValid(const std::string& name)
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