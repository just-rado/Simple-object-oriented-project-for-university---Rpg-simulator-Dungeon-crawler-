#pragma once
#include <string>
class SystemState
{
public:
	virtual int display() = 0;
	virtual SystemState* execute(int action) = 0;

	virtual ~SystemState() = default;
protected:
	static bool tryAgain(const std::string& error);
	static std::string getString(const std::string& output);
};

