#include "HeroFactory.h"
#include "Warrior.h"
#include "Mage.h"
#include "Healer.h"
#include "Paladin.h"

 Hero* HeroFactory::loadHeroFromFile(std::ifstream& is, HeroClass type)
{
	switch (type)
	{
	case HeroClass::WARRIOR:
		return new Warrior(is);
	case HeroClass::MAGE:
		return new Mage(is);
	case HeroClass::PALADIN:
		return new Paladin(is);
	case HeroClass::HEALER:
		return new Healer(is);
	default:
		return nullptr;
	}
	
}

Hero* HeroFactory::createNewHero(const std::string& name, HeroClass cl)
{
	switch (cl)
	{
	case HeroClass::WARRIOR:
		return new Warrior(name);
	case HeroClass::MAGE:
		return new Mage(name);
	case HeroClass::PALADIN:
		return new Paladin(name);
	case HeroClass::HEALER:
		return new Healer(name);
	default:
		return nullptr;
	}
}