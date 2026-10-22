#include "EnemyFactory.h"
#include "Skeleton.h"
#include "Werewolf.h"

Enemy* EnemyFactory::readEnemyFromFile(std::ifstream& is , TypeOfEnemy type)
{
	switch (type)
	{
	case TypeOfEnemy::SKELETON:
		return new (std::nothrow)Skeleton(is);
	case TypeOfEnemy::WEREWOLF:
		return new (std::nothrow)Werewolf(is);
	default:
		return nullptr;
	}
}