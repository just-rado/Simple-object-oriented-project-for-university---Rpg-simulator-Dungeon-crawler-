#pragma once
#include <cstdint> // for uint8_t
// keeps track of how many hero classes have been created
enum  class HeroClass : uint8_t
{
	PALADIN,
	MAGE,
	HEALER,
	NUM_CLASSES,
};

size_t getAmountOfHeroClasses();

void printHeroClass(HeroClass heroClass);
