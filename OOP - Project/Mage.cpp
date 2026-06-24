#include "Mage.h"
#include <stdexcept>
#include <iostream>

Mage::Mage(const std::string& name): Hero(createMageData(name) , HERO_CLASS) , spells()
{

}
Mage::Mage(const Mage& other): Hero(other)
{
	deepCopySpells(other.spells);
}
Mage& Mage::operator=(const Mage& other)
{
	if (this != &other)
	{
		Mage temp(other);
		swap(temp);
	}
	return *this;
}
Mage::~Mage()
{
	free(this->spells);
}
Hero* Mage::clone()const
{
	return new Mage(*this);
}


size_t Mage::getNumberOfAbilites()const
{
	return NUMBER_OF_ABILITIES;
}

void Mage::printAbilities()const
{
	std::cout << "Abilities:\n" << "Ability 1: Cast a spell at a target\n";
}

bool Mage::requiresATarget(size_t ability)const
{
	if (ability == 1)
	{
		return true;
	}
	return false;
}

bool Mage::useAbility(size_t ability, Character* character)
{	
	if (ability == 1)
	{
		if (!character)
		{
			return false;
		}

		size_t spell = 0;
		size_t numberOfSpells = this->spells.size();
		std::cout << "Pick a spell to cast:\n";
		for (size_t i = 0; i < numberOfSpells; ++i)
		{
			std::cout << i << ". " <<  this->spells[i]->getName() << "\nDescription : " << this->spells[i]->getDescription() << '\n';
		}
		std::cin >> spell;

		if (spell >= numberOfSpells)
		{
			return false;
		}
		
		return abilityCastSpellAtCharacter(character, spell);
	}
	return false;
}

size_t Mage::getNumberOfSpells()const
{
	return this->spells.size();
}
const Spell* Mage::getSpell(size_t index)const
{
	if (index >= this->spells.size())
	{
		return nullptr;
	}
	return this->spells[index];
}

bool Mage::abilityCastSpellAtCharacter(Character* character , size_t numberOfSpell)
{
	if (this->spells[numberOfSpell]->getManaCost() > this->getMP())
	{
		std::cout << "Not enough mana!\n";
		return false;
	}

	this->setMP(this->getMP() - this->spells[numberOfSpell]->getManaCost());

	return this->spells[numberOfSpell]->applyEffectOfSpell(character);
}

bool Mage::learnSpell(const Spell* spell)
{
	if (!spell)
	{
		return false;
	}

	if (spell->getLevelRequired() > this->getCurrentLevel())
	{
		return false;
	}
	size_t numberOfSpells = this->spells.size();
	for (size_t i = 0; i < numberOfSpells; ++i)
	{
		if (this->spells[i]->getName() == spell->getName())
		{
			return false;
		}
	}

	Spell* temp = spell->clone();
	if (!temp)
	{
		return false;
	}
	try
	{	
		this->spells.push_back(temp);
	}
	catch (...)
	{
		delete temp;
		return false;
	}
	

	return true;
}

void Mage::updateMainStats(int numberOfTimes)
{
	this->setSTR(this->getSTR() + 2 * numberOfTimes);
	this->setINT(this->getINT() + 5 * numberOfTimes);
	this->setAGI(this->getAGI() + 2 * numberOfTimes);

	this->updateMaxHP(this->getMaxHP() + 25 * numberOfTimes);
	this->updateMaxMP(this->getMaxMP() + 50 * numberOfTimes);

	this->setHP(this->getMaxHP());
	this->setMP(this->getMaxMP());
}


CharacterData Mage::createMageData(const std::string name)
{
	CharacterData data;
	data.name = name;

	data.mainStats.STR = 5;
	data.mainStats.INT = 30;
	data.mainStats.AGI = 10;
	data.mainStats.DEF = 1;

	data.maxHP = 300;
	data.maxMP = 200;

	data.mainStats.currentHP = data.maxHP;
	data.mainStats.currentMP = data.maxMP;

	data.currentLevel = 1;
	data.goldCoinsOwned = 0;

	data.statusEffects.clear();

	return data;
}

void Mage::swap(Mage& other)noexcept
{
	Hero::swap(other);
	std::swap(this->spells, other.spells);
}
	 
void Mage::deepCopySpells(const std::vector<Spell*>& spells)
{
	std::vector<Spell*> toDelete = std::move(this->spells);
	Spell* temp = nullptr;
	try
	{
		this->spells.clear();
		size_t size = spells.size();
		for (size_t i = 0; i < size; ++i)
		{
			if (!spells[i])
			{
				throw std::invalid_argument("Error");
			}
			temp = spells[i]->clone();
			if (!temp)
			{
				throw std::bad_alloc();
			}
			this->spells.push_back(temp);
		}
	}
	catch (...)
	{
		delete temp;

		free(this->spells);
		this->spells = std::move(toDelete);
		throw;
	}
	free(toDelete);
}
void Mage::free(std::vector<Spell*>& spells)
{
	size_t size = spells.size();
	for (size_t i = 0; i < size; ++i)
	{
		delete spells[i];
	}
	spells.clear();
}
