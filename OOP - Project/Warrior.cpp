#include "Warrior.h"
#include "Item.h"
#include "Weapon.h"
#include <random>

Warrior::Warrior(const std::string& name) : Hero(createWarriorData(name) , Warrior::heroClass) , tauntUsed(false) , 
					remainingTurnsOfTauntEffect(0)
{
	
}

void Warrior::tauntEnemies()
{
	int costOfAbility = 25;
	if (this->getMP() - costOfAbility >= 0)
	{
		this->tauntUsed = true;
		this->remainingTurnsOfTauntEffect = 2;
		this->setMP(this->getMP() - costOfAbility);
	}
	
}

void Warrior::attackEnemy(Enemy* enemy)
{
	int inflictDamage = 0;
	inflictDamage += this->getSTR();
	const Weapon* weapon = dynamic_cast<const Weapon*>(this->getItemFromEquippedItems(TypeOfItem::WEAPON));
	if (weapon)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<> chance(1, 100);

		int amplifier = 1;
		if (chance(gen) <= weapon->getCriticalChance())
		{
			amplifier = 2;
		}

		inflictDamage += weapon->getDmgValue() * amplifier;

		size_t size = enemy->getNumberOfWeaknesses();
		AgmentationType damageTypeOfWeapon = weapon->getDmgType();
		for (size_t i = 0; i < size; ++i)
		{
			if (enemy->getWeakTo(i) == damageTypeOfWeapon)
			{
				inflictDamage *= 2;
				break;
			}
		}
	}

	inflictDamage /=  enemy->getDEF();
	int newHP = enemy->getHP() - inflictDamage;
	enemy->setHP(newHP);
	if (enemy->getHP() == 0)
	{
		this->setGoldCoins(this->getGoldCoins() + enemy->getGoldCoins());
		this->setLevel(this->getCurrentLevel() + enemy->getExpGainedForKilling());
	}
}

Hero* Warrior::clone()const
{
	return new Warrior(*this);
}

CharacterData Warrior::createWarriorData(const std::string& name)
{
	CharacterData data;
	data.name = name;

	data.mainStats.STR = 30;
	data.mainStats.INT = 10;
	data.mainStats.AGI = 5;
	
	data.mainStats.DEF = calculateDefence(data.mainStats);

	data.maxHP = calculateMaxHP(data.mainStats);
	data.maxMP = calculateMaxMP(data.mainStats);
	
	data.mainStats.HP = data.maxHP;
	data.mainStats.MP = data.maxMP;

	data.currentLevel = 1;
	data.goldCoinsOwned = 0;
	
	data.statusEffects.clear();

	return data;
}


unsigned int Warrior::calculateMaxHP(const CharacterStats& stats)
{
	return Warrior::BASE_HP + stats.STR * Hero::STR_TO_HEALTH_MULTIPLIER;
}
unsigned int Warrior::calculateMaxMP(const CharacterStats& stats)
{
	return Warrior::BASE_MP + stats.INT * Hero::INT_TO_MANA_MULTIPLIER;
}
unsigned int Warrior::calculateDefence(const CharacterStats& stats)
{
	return Warrior::BASE_DEFENCE + stats.AGI * Hero::AGI_TO_DEF_MULTIPLIER;
}