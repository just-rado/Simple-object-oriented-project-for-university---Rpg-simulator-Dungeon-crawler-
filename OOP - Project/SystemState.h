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
	State getState()const;

	virtual ~SystemState() = default;
protected:
	void changeState();
	static bool tryAgain(const std::string& error);
	static std::string getString(const std::string& output);
	
private:
	State state;
	
	
};

