#pragma once
#include <iostream>
struct CharacterStats
{
	int currentHP; 
	int currentMP;
	int STR;
	int INT;
	int AGI;
	int DEF;

};

inline void printCharacterStats(const CharacterStats& modifiers)
{
	std::cout << "Health modifier: " << modifiers.currentHP << '\n';
	std::cout << "Mana modifier: " << modifiers.currentMP << '\n';
	std::cout << "Strength modifier: " << modifiers.STR << '\n';
	std::cout << "Intelligence modifier: " << modifiers.INT << '\n';
	std::cout << "Agility modfier: " << modifiers.AGI << '\n';
	std::cout << "Defence modfier: " << modifiers.DEF << '\n';
}

 