#pragma once
#include <iostream>
enum class AugmentationType : uint32_t
{
	PHYSICAL,
	FIRE,
	ICE,
	LIGHTNING,
	HOLY,
	Nature,
	NONE,

};

enum class StatusEffectType : uint32_t
{
	POISON,
	CURSE,
	BLESSING,
	PROTECTION,
	NONE,

};

inline void printStatusEffect(StatusEffectType type)
{
	switch (type)
	{
	case StatusEffectType::POISON:
		std::cout << "Poison\n";
		break;
	case StatusEffectType::CURSE:
		std::cout << "Curse\n";
		break;
	case StatusEffectType::BLESSING:
		std::cout << "Blessing\n";
		break;
	case StatusEffectType::PROTECTION:
		std::cout << "Protection\n";
		break;
	default:
		std::cout << "None\n";
		break;
	}
}


inline void printAugmentationType(AugmentationType type)
{
	switch (type)
	{
	case AugmentationType::FIRE:
		std::cout << "Fire\n";
		break;
	case AugmentationType::HOLY:
		std::cout << "Holy\n";
		break;
	case AugmentationType::ICE:
		std::cout << "Ice\n";
		break;
	case AugmentationType::LIGHTNING:
		std::cout << "Lightning\n";
		break;
	case AugmentationType::Nature:
		std::cout << "Nature\n";
		break;
	case AugmentationType::PHYSICAL:
		std::cout << "Physical\n";
		break;
	default:
		std::cout << "None\n";
		break;
	}
}