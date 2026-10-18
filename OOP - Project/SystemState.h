#pragma once
#include <string>
enum class State
{
	DEFAULT,
	BACK,
};
class SystemState
{
public:
	SystemState();

	virtual int display() = 0;
	virtual SystemState* execute(int action) = 0;

	virtual ~SystemState() = default;
protected:
	State state;
	static bool tryAgain(const std::string& error);
	static std::string getString(const std::string& output);
	

	void changeState();
	State getState()const;
};

