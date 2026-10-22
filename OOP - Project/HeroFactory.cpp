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
		return new (std::nothrow)Warrior(is);
	case HeroClass::MAGE:
		return new (std::nothrow)Mage(is);
	case HeroClass::PALADIN:
		return new (std::nothrow)Paladin(is);
	case HeroClass::HEALER:
		return new (std::nothrow)Healer(is);
	default:
		return nullptr;
	}
	
}

Hero* HeroFactory::createNewHero(const std::string& name, HeroClass cl)
{
	switch (cl)
	{
	case HeroClass::WARRIOR:
		return new (std::nothrow)Warrior(name);
	case HeroClass::MAGE:
		return new (std::nothrow)Mage(name);
	case HeroClass::PALADIN:
		return new (std::nothrow)Paladin(name);
	case HeroClass::HEALER:
		return new (std::nothrow)Healer(name);
	default:
		return nullptr;
	}
}