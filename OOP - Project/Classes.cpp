#include "Classes.h"
#include <iostream>

size_t getAmountOfHeroClasses()
{
	return static_cast<size_t>(HeroClass::NUM_CLASSES);
}


void printHeroClass(HeroClass heroClass)
{
	switch (heroClass)
	{
	case HeroClass::WARRIOR:
		std::cout << "Warrior\n";
		break;
	case HeroClass::PALADIN:
		std::cout << "Paladin\n";
		break;
	case HeroClass::MAGE:
		std::cout << "Mage\n";
		break;
	case HeroClass::HEALER:
		std::cout << "Healer\n";
		break;
	default:
		std::cout << "Unknown class\n";
		break;
	}

}