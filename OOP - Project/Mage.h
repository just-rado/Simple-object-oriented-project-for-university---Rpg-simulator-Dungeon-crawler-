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

	bool learnSpell(const Spell* spell);
	
	virtual size_t getNumberOfAbilites()const override;
	virtual void printAbilities()const override;
	virtual bool requiresATarget(size_t ability)const override;
	virtual bool useAbility(size_t ability, Character* character)override;
	
	

	size_t getNumberOfSpells()const;
	const Spell* getSpell(size_t index)const;

	virtual Hero* clone()const override;


protected:
	void swap(Mage& other)noexcept;
	virtual void updateMainStats(int numberOfTimes)override;
	bool abilityCastSpellAtCharacter(Character* character, size_t numberOfSpell);
private:
	
	std::vector<Spell*> spells;



	void deepCopySpells(const std::vector<Spell*>& spells);
	void free(std::vector<Spell*>& spells);

	static CharacterData createMageData(const std::string name);

	static constexpr size_t NUMBER_OF_ABILITIES = 1;
	static constexpr HeroClass HERO_CLASS = HeroClass::MAGE;
	
};

