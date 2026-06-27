#pragma once
#include "Hero.h"
#include "CharacterStats.h"
#include "Classes.h"
#include <string>

class Warrior: public virtual Hero
{
public:
	Warrior(const std::string& name);

	Warrior(std::ifstream& read);
	virtual void writeToFile(std::ofstream& write)const override;

	virtual void updateStatusOfCharacter()override;
	virtual void printAbilities()const override;
	virtual size_t getNumberOfAbilites()const override;
	virtual bool requiresATarget(size_t ability)const override;
	virtual bool useAbility(size_t ability, Character* character)override;
	virtual int calculatePriority()const override;

	bool isTauntUsed()const;

	virtual Hero* clone()const override;
	
protected:
	virtual void updateMainStats(int numberOfTimes)override;
	bool abilityTauntEnemies();
	void writeOwnDataToFile(std::ofstream& write)const;
	
private:
	bool tauntUsed;
	unsigned int remainingTurnsOfTauntEffect;

	
	static CharacterData createWarriorData(const std::string& name);

	static constexpr HeroClass HERO_CLASS = HeroClass::WARRIOR;

	static constexpr size_t NUMBER_OF_ABILITIES = 1;

};

