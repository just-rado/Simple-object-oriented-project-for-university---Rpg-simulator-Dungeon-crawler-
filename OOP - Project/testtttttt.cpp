#include <iostream>
#include "Classes.h"
#include "Armor.h"
#include "Weapon.h"
#include "Consumable.h"
#include "Hero.h"
#include "Character.h"
#include "Room.h"
int main()
{
	uint64_t x = 7;


	uint64_t one = 1;
	uint64_t find = 0;

	size_t index = 0;
	size_t size = getAmountOfHeroClasses();
	for (size_t i = 0; i < size; ++i)
	{
	
		find = one << (i %64);
		find = (find & x);
		if (find != 0)
		{
			printHeroClass(static_cast<HeroClass>(i));
		}
	}

	

	return 0;
}