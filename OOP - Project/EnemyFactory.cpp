#include "EnemyFactory.h"
#include "Skeleton.h"
#include "Werewolf.h"

Enemy* EnemyFactory::readEnemyFromFile(std::ifstream& is , TypeOfEnemy type)
{
	switch (type)
	{
	case TypeOfEnemy::SKELETON:
		return new Skeleton(is);
	case TypeOfEnemy::WEREWOLF:
		return new Werewolf(is);
	default:
		return nullptr;
	}
}