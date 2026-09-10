#pragma once
#include "Hero.h"
#include "Classes.h"
#include <fstream>
#include <string>
class HeroFactory
{
public:

	static Hero* loadHeroFromFile(std::ifstream& is, HeroClass type);
	
	static Hero* createNewHero(const std::string& name, HeroClass cl);
	

};

