#pragma once
// keeps track of how many hero classes have been created
enum  class HeroClass 
{
	WARRIOR,
	MAGE,
	HEALER,
	PALADIN,
	NUM_CLASSES,
};

size_t getAmountOfHeroClasses();

void printHeroClass(HeroClass heroClass);
