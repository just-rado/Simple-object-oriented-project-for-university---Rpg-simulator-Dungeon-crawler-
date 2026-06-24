#pragma once
#include "Enemy.h"
#include <string>
class Skeleton : public Enemy
{
public:
	Skeleton(const std::string& name);
	Skeleton(const Skeleton& other);
	Skeleton& operator=(const Skeleton& other) = delete;
	virtual ~Skeleton()override;

	bool addItem(const Item* item);

	virtual const Item* itemDropped()override;
	virtual Enemy* clone()const override;

protected:
	virtual void updateMainStats(int numberOfTimes)override;

private:
	Item* item;

	static CharacterData createSkeletonData(const std::string& name);

	static constexpr TypeOfEnemy ENEMY_TYPE = TypeOfEnemy::SKELETON;

	static constexpr int BASE_CHANCE_OF_ITEM_DROP = 10;
	static constexpr float BASE_EXP_GIVEN = 0.1f;
};

