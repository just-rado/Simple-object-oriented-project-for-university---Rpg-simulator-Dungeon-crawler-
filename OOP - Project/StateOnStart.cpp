#include "StateOnStart.h"
#include <iostream>
#include "SafeInputReading.h"
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

