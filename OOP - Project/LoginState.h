#pragma once
#include "SystemState.h"
#include <string>
class LoginState: public SystemState
{
public:

	int display()override;
	SystemState* execute(int action)override;

private:

	std::string loginPrompt();
};

