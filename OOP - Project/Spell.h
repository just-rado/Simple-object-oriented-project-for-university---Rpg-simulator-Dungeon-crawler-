#pragma once


enum class TypeOfSpell
{
	DAMAGE,
	HEAL,
	CLEANSE,
};
enum class EffectOfSpell
{
	FIRE,
	ICE,
	ARCANE,
	NATURE,
	HOLY,

};


class Spell
{
public:

	Spell(TypeOfSpell type, EffectOfSpell effect);

	virtual ~Spell() = default;

	virtual Spell* clone()const = 0;

	TypeOfSpell getEffect()const;
	EffectOfSpell getType()const;

private:
	TypeOfSpell type;
	EffectOfSpell effect;
	


};

