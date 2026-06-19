#include "Enemy.h"

Enemy::Enemy(const CharacterData& mainStats, TypeOfEnemy type, const std::vector<AgmentationType> weakTo , unsigned int exp): 
	Character(mainStats), type(type) , weakTo(weakTo) , experienceGivenIfKilled(exp)
{

}


TypeOfEnemy Enemy::getType()const
{
	return this->type;
}

const size_t Enemy::getNumberOfWeaknesses()const
{
	return this->weakTo.size();
}
const AgmentationType Enemy::getWeakTo(size_t index)const
{
	return this->weakTo[index];
}


unsigned int Enemy::getExpGainedForKilling()const
{
	return this->experienceGivenIfKilled;
}