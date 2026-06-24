#include "Werewolf.h"

Werewolf::Werewolf(const std::string& name): Enemy(createWerewolfData(name) , ENEMY_TYPE , BASE_EXP_GIVEN)
{
	
}

Werewolf::Werewolf(std::ifstream& read): Enemy(read , ENEMY_TYPE)
{

}
void Werewolf::writeToFile(std::ofstream& write)const
{
	Enemy::writeOwnDataToFile(write);
	writeOwnDataToFile(write);
}

void Werewolf::writeOwnDataToFile(std::ofstream& write)const
{
	return;
}
Enemy* Werewolf::clone()const
{
	return new Werewolf(*this);
}

bool Werewolf::attackHero(Hero* hero)
{
	if (!hero)
	{
		return false;
	}
	
	int blessingMultiplier = 1;
	size_t numberOfStatusEffects = this->getNumberOfStatusEffects();
	for (size_t i = 0; i < numberOfStatusEffects; ++i)
	{
		StatusEffectType type = this->getStatusEffect(i).typeOfEffect;
		
		if (type == StatusEffectType::BLESSING)
		{
			blessingMultiplier = 3;
			break;
		}

	}

	int inflictDamage = this->calculateDamage() * blessingMultiplier;

	size_t numberOfEnemyStatusEffects = hero->getNumberOfStatusEffects();
	int protectionMultiplier = 1;
	for (size_t i = 0; i < numberOfEnemyStatusEffects; ++i)
	{
		if (hero->getStatusEffect(i).typeOfEffect == StatusEffectType::PROTECTION)
		{
			protectionMultiplier = 2;
			break;
		}
	}

	unsigned int def = hero->calculateDefence();
	if (def != 0)
	{
		inflictDamage /= (def * protectionMultiplier);
	}


	int newHP = hero->getHP() - inflictDamage;
	hero->setHP(newHP);

	if (hero->getHP() == 0)
	{
		this->setGoldCoins(this->getGoldCoins() + hero->getGoldCoins());
	}

	return true;

}

unsigned int Werewolf::calculateDamage()const
{
	int missingHealth = this->getMaxHP() - this->getHP();
	int bonusDMG = missingHealth * 0.1;
	return this->getSTR() * STR_TO_ATTACK_DMG_MULTIPLIER + bonusDMG;
}


void Werewolf::updateMainStats(int numberOfTimes)
{
	this->setSTR(this->getSTR() + 5 * numberOfTimes);
	this->setINT(this->getINT() + 2 * numberOfTimes);
	this->setAGI(this->getAGI() + 2 * numberOfTimes);

	this->updateMaxHP(this->getMaxHP() + 150 * numberOfTimes);
	this->updateMaxMP(this->getMaxMP() + 20 * numberOfTimes);

	this->setHP(this->getMaxHP());
	this->setMP(this->getMaxMP());
}
 

CharacterData Werewolf::createWerewolfData(const std::string& name)
{
	CharacterData data;
	data.name = name;

	data.mainStats.STR = 30;
	data.mainStats.INT = 10;
	data.mainStats.AGI = 10;
	data.mainStats.DEF = 0;

	data.maxHP = 500;
	data.maxMP = 100;


	data.mainStats.currentHP = data.maxHP;
	data.mainStats.currentMP = data.maxMP;

	data.currentLevel = 1;
	data.goldCoinsOwned = 0;

	data.statusEffects.clear();

	return data;
}