#include <iostream>
#include "Hero.h"
#include "Healer.h"
#include "Mage.h"
#include "Warrior.h"
#include "Paladin.h"
#include "Enemy.h"
#include "Skeleton.h"
#include "Werewolf.h"
#include <string>

int main()
{
	std::string name("rado");
	Hero* healer = new Healer(name);

	std::string name1("petar");
	Hero* mage = new Mage(name1);

	std::string name2("anna");
	Hero* warrior = new Warrior(name2);
	
	std::string name3("valieri");
	Hero* paladin = new Paladin(name3);

	std::string name4("skeleton");
	Enemy* skeleton = new Skeleton(name4);

	std::string name5("werewolf");
	Enemy* werewolf = new Werewolf(name5);


	


	delete healer;
	delete mage;
	delete warrior;
	delete paladin;
	delete skeleton;
	delete werewolf;
	return 0;
}