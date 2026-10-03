#include "StateOnStart.h"
#include <iostream>
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
		std::cin >> action;
		if (action > 0 && action < 5)
		{
			return action;
		}
		else
		{
			std::cout << "Invalid input. Try again\n\n\n\n\n";
		}
	}
}

