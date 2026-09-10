#pragma once
#include "Enemy.h"
#include <fstream>
class EnemyFactory
{
public:
	static Enemy* readEnemyFromFile(std::ifstream& is , TypeOfEnemy type);
};

