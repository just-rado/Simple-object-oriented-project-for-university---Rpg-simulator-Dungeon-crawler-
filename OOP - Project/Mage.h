#pragma once
#include "Hero.h"
#include "Spell.h"
#include <vector>
#include <string>
class Mage: public Hero
{
public:
	Mage(const std::string& name);
	Mage(const Mage& other);
	Mage& operator=(const Mage& other);
	virtual ~Mage()override;

	virtual void attackEnemy(Enemy* enemy);

	virtual Hero* clone()const;

protected:
	void swap(Mage& other)noexcept;
private:
	
	std::vector<Spell*> spells;

	void deepCopySpells(const std::vector<Spell*> spells);
	void free(std::vector<Spell*>& spells);

	static unsigned int calculateMaxHP(const CharacterStats& stats);
	static unsigned int calculateMaxMP(const CharacterStats& stats);
	static unsigned int calculateDefence(const CharacterStats& stats);

	static CharacterData& createMageData(const std::string name);

	static constexpr HeroClass HERO_CLASS = HeroClass::MAGE;
	static constexpr unsigned int BASE_HP = 300;
	static constexpr unsigned int BASE_MP = 200;
	static constexpr unsigned int BASE_DEFENCE = 1;
};

