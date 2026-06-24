#include "Healer.h"
#include <stdexcept>
#include <iostream>

Healer::Healer(const std::string& name) : Hero(createHealerData(name) , HERO_CLASS) , healSpells()
{

}
Healer::Healer(const Healer& other) : Hero(other)
{
	deepCopySpells(other.healSpells);
}
Healer& Healer::operator=(const Healer& other)
{
	if (this != &other)
	{
		Healer copy(other);
		swap(copy);
	}
	return *this;
}
Healer::~Healer()
{
	free(this->healSpells);
}

void Healer::swap(Healer& other)noexcept
{
	Hero::swap(other);
	std::swap(this->healSpells, other.healSpells);
}


bool Healer::attackEnemy(Enemy* enemy)
{
	std::cout << "Healers are pacifists\n";
	return false;
}

bool Healer::learnHealSpell(const HealSpell* spell)
{
	if (!spell)
	{
		return false;
	}

	if (spell->getLevelRequired() > this->getCurrentLevel())
	{
		return false;
	}

	size_t numberOfSpells = this->healSpells.size();
	for (size_t i = 0; i < numberOfSpells; ++i)
	{
		if (this->healSpells[i]->getName() == spell->getName())
		{
			return false;
		}
	}
	HealSpell* temp = nullptr;
	try
	{
		temp = new HealSpell(*spell);
		this->healSpells.push_back(temp);
	}
	catch (...)
	{
		delete temp;
		return false;
	}
	

	return true;

}

bool Healer::useAbility(size_t ability, Character* character)
{

	if (ability == 1)
	{
		if (!character)
		{
			return false;
		}

		size_t healSpell = 0;
		size_t numberOfSpells = this->healSpells.size();
		std::cout << "Pick a healing spell to cast:\n";
		for (size_t i = 0; i < numberOfSpells; ++i)
		{
			std::cout << i << ". " << this->healSpells[i]->getName() << "\nDescription : " << this->healSpells[i]->getDescription() << '\n';
		}
		std::cin >> healSpell;

		if (healSpell >= numberOfSpells)
		{
			return false;
		}
		
		return abilityCastHealSpellAtCharacter(character, healSpell);
		
	}
	return false;
}
size_t Healer::getNumberOfAbilites()const
{
	return NUMBER_OF_ABILITIES;
}
void Healer::printAbilities()const
{
	std::cout << "Abilities:\n" << "Ability 1: Cast a healing spell at target\n";
}
bool Healer::requiresATarget(size_t ability)const
{
	if (ability == 1)
	{
		return true;
	}
	return false;
}

bool Healer::abilityCastHealSpellAtCharacter(Character* character, size_t numberOfSpell)
{
	if (this->healSpells[numberOfSpell]->getManaCost() > this->getMP())
	{
		std::cout << "Not enough mana!\n";
		return false;
	}

	this->setMP(this->getMP() - this->healSpells[numberOfSpell]->getManaCost());

	return this->healSpells[numberOfSpell]->applyEffectOfSpell(character);
	
}

size_t Healer::getNumberOfHealSpells()const
{
	return this->healSpells.size();
}
const HealSpell* Healer::getHealSpell(size_t index)const
{
	if (index >= this->healSpells.size())
	{
		return nullptr;
	}
	return this->healSpells[index];
}

unsigned int Healer::calculateDamage()const
{
	return 0;
}

Hero* Healer::clone()const
{
	return new Healer(*this);
}

void Healer::updateMainStats(int numberOfTimes)
{
	this->setSTR(this->getSTR() + 3 * numberOfTimes);
	this->setINT(this->getINT() + 4 * numberOfTimes);
	this->setAGI(this->getAGI() + 1 * numberOfTimes);

	this->updateMaxHP(this->getMaxHP() + 30 * numberOfTimes);
	this->updateMaxMP(this->getMaxMP() + 40 * numberOfTimes);

	this->setHP(this->getMaxHP());
	this->setMP(this->getMaxHP());
}
CharacterData Healer::createHealerData(const std::string& name)
{
	CharacterData data;
	data.name = name;

	data.mainStats.STR = 10;
	data.mainStats.INT = 25;
	data.mainStats.AGI = 5;
	data.mainStats.DEF = 0;

	data.maxHP = 350;
	data.maxMP = 150;

	data.mainStats.currentHP = data.maxHP;
	data.mainStats.currentMP = data.maxMP;

	data.currentLevel = 1;
	data.goldCoinsOwned = 0;

	data.statusEffects.clear();

	return data;
}


void Healer::deepCopySpells(const std::vector<HealSpell*>& spells)
{
	std::vector<HealSpell*> toDelete = std::move(this->healSpells);
	HealSpell* temp = nullptr;
	try
	{
		this->healSpells.clear();
		size_t size = spells.size();
		for (size_t i = 0; i < size; ++i)
		{
			if (!spells[i])
			{
				throw std::invalid_argument("Error");
			}
			temp = new (std::nothrow) HealSpell(*spells[i]);
			if (!temp)
			{
				throw std::bad_alloc();
			}
			this->healSpells.push_back(temp);
		}
	}
	catch (...)
	{
		delete temp;

		free(this->healSpells);
		this->healSpells = std::move(toDelete);
		throw;
	}
	free(toDelete);
}
void Healer::free(std::vector<HealSpell*>& spells)
{
	size_t size = spells.size();
	for (size_t i = 0; i < size; ++i)
	{
		delete spells[i];
	}
	spells.clear();
}