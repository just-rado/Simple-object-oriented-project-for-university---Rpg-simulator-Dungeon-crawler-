#pragma once
#include "Hero.h"
#include "CharacterStats.h"
#include "Classes.h"
#include <string>

class Warrior: public Hero
{
public:
	Warrior(const std::string& name);

	void tauntEnemies();

	virtual void attackEnemy(const Enemy* enemy)override;
	virtual Hero* clone()const override;

private:
	bool tauntUsed;
	unsigned int remainingTurnsOfTauntEffect;

	static unsigned int calculateMaxHP(const CharacterStats& stats);
	static unsigned int calculateMaxMP(const CharacterStats& stats);
	static unsigned int calculateDefence(const CharacterStats& stats);
	static CharacterData createWarriorData(const std::string& name);

	static constexpr HeroClass heroClass = HeroClass::WARRIOR;

	static constexpr unsigned int BASE_HP = 500;
	static constexpr unsigned int BASE_MP = 100;
	static constexpr unsigned int BASE_DEFENCE = 5;

};

