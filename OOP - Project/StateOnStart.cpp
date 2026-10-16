#include "StateOnStart.h"
#include <iostream>
#include "SafeInputReading.h"
#include "RegisterState.h"
int StateOnStart::display()
{
	while (true)
	{
		std::cout << "Choose an option:\n";
		std::cout << "1.Register\n";
		std::cout << "2.Login\n";
		std::cout << "3.Creator mode\n";
		std::cout << "4.Quit\n";

		int action = 0;
		
		if (!readValidInt(1, 4, action))
		{
			if (!tryAgain("Invalid input"))
			{
				return 4;
			}
			else
			{
				continue;
			}
		}
		return action;
	}
}

SystemState* StateOnStart::execute(int action)
{
	switch (action)
	{
	case 1:
		return new RegisterState();
	case 2:
		//login
		return nullptr;
	case 3:
		// creator
		return nullptr;
	case 4:
		return nullptr;

	}
}

