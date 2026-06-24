#pragma once
#include "Hero.h"
#include "Warrior.h"
#include "Healer.h"
#include <string>

class Paladin : public Warrior , public Healer
{
public:
	Paladin(const std::string& name);

	Paladin(std::ifstream& read);
	virtual void writeToFile(std::ofstream& write)const override;

	virtual void updateStatusOfCharacter()override;

	virtual void printAbilities()const override;
	virtual size_t getNumberOfAbilites()const override;
	virtual bool requiresATarget(size_t ability)const override;
	virtual bool useAbility(size_t ability, Character* character)override;

	virtual unsigned int calculateDamage()const override;
	virtual bool attackEnemy(Enemy* enemy)override;
	virtual Hero* clone()const override;

protected:
	virtual void updateMainStats(int numberOfTimes)override;
	void writeOwnDataToFile(std::ofstream& write)const;
private:

	static CharacterData createPaladinData(const std::string& name);

	static constexpr HeroClass HERO_CLASS = HeroClass::PALADIN;

	static constexpr size_t NUMBER_OF_ABILITIES = 2;

};

