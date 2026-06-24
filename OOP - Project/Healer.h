#pragma once
#include "Hero.h"
#include "HealSpell.h"
#include <vector>
#include <string>
class Healer: public virtual Hero
{
public:
	Healer(const std::string& name);

	Healer(std::ifstream& read);
	virtual void writeToFile(std::ofstream& write)const override;

	Healer(const Healer& other);
	Healer& operator=(const Healer& other);
	virtual ~Healer()override;

	bool learnHealSpell(const HealSpell* spell);

	virtual bool useAbility(size_t ability, Character* character) override;
	virtual size_t getNumberOfAbilites()const override;
	virtual void printAbilities()const override;
	virtual bool requiresATarget(size_t ability)const override;
	

	virtual bool attackEnemy(Enemy* enemy)override;

	size_t getNumberOfHealSpells()const;
	const HealSpell* getHealSpell(size_t index)const;

	virtual unsigned int calculateDamage()const override;
	virtual Hero* clone()const override;

protected:
	void swap(Healer& other)noexcept;
	virtual void updateMainStats(int numberOfTimes)override;
	bool abilityCastHealSpellAtCharacter(Character* character, size_t numberOfSpell);
	void writeOwnDataToFile(std::ofstream& write)const;
private:
	std::vector<HealSpell*> healSpells;

	static CharacterData createHealerData(const std::string& name);

	static constexpr HeroClass HERO_CLASS = HeroClass::HEALER;

	static constexpr size_t NUMBER_OF_ABILITIES = 1;

	void deepCopySpells(const std::vector<HealSpell*>& spells);
	void free(std::vector<HealSpell*>& spells);
};

