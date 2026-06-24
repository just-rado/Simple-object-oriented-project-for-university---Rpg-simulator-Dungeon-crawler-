#pragma once
#include "Enemy.h"
class Werewolf: public Enemy
{
public:
	Werewolf(const std::string& name);
	Werewolf& operator=(const Werewolf& other) = delete;

	virtual Enemy* clone()const override;

	virtual bool attackHero(Hero* hero)override;

	virtual unsigned int calculateDamage()const override;
protected:
	virtual void updateMainStats(int numberOfTimes)override;
private:

	static CharacterData createWerewolfData(const std::string& name);

	static constexpr TypeOfEnemy ENEMY_TYPE = TypeOfEnemy::WEREWOLF;

	static constexpr float BASE_EXP_GIVEN = 0.4f;
};

