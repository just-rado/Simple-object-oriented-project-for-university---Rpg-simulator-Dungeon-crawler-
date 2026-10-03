#pragma once
#include "SystemState.h"
#include <string>
class RegisterState : public SystemState
{
public:

	int display() override;
	SystemState* execute(int action)override;

private:
	static bool doesAccountAlreadyExist(const std::string& userName);
	static bool createAccount(const std::string& userName, const std::string& password);
	

};

