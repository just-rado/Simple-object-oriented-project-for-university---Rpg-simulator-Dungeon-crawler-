#include <iostream>
#include <string>
#include <vector>
#include "Hero.h"
#include "Healer.h"
#include "Mage.h"
#include "Warrior.h"
#include "Paladin.h"
#include "Enemy.h"
#include "Skeleton.h"
#include "Werewolf.h"
#include "Spell.h"
#include "HealSpell.h"
#include "DamageSpell.h"
#include "CleanseSpell.h"
#include "Item.h"
#include "Relic.h"
#include "Weapon.h"
#include "Armor.h"
#include "Scroll.h"
#include "Consumable.h"
int main()
{
	std::ifstream file("itemFile.bin", std::ios::binary);
	if (!file.is_open())
	{
		return 1;
	}
	uint32_t itemTypeValue = 0;
	file.read(reinterpret_cast<char*>(&itemTypeValue), sizeof(itemTypeValue));
	uint64_t id = 0;
	file.read(reinterpret_cast<char*>(&id), sizeof(id));

	Item* shouldBeWeapon = nullptr;
	TypeOfItem type = static_cast<TypeOfItem>(itemTypeValue);
	switch (type)
	{
	case TypeOfItem::WEAPON:
		shouldBeWeapon = new Weapon(file , id);
		
		break;
	case TypeOfItem::ARMOR:
		std::cout << "yayArmor";
		break;
	case TypeOfItem::CONSUMABLE:
		std::cout << "yayCon";
		break;
	case TypeOfItem::SCROLL:
		std::cout << "yayScro";

		break;
	case TypeOfItem::RELIC:
		std::cout << "yayRelic";
		break;
	default:
		std::cout << "nay";
		break;
	}

	std::cout << shouldBeWeapon->getName();
	delete shouldBeWeapon;

	file.close();
	/*ItemData A1;
	A1.name = "Heavenly weapon";
	A1.rarity = Rarity::LEGENDARY;
	A1.costInGoldCoins = 100;
	A1.weightInKg = 10;
	A1.requiredLevel = 10;
	A1.compatibleClasses.push_back(1);

	AugmentationType type = AugmentationType::HOLY;
	unsigned int dmgVal = 1000;
	unsigned int criticalChance = 100;

	Item* first = new Weapon(A1, type, dmgVal, criticalChance);

	A1.name = "Curse armor";
	A1.rarity = Rarity::LEGENDARY;
	A1.costInGoldCoins = 200;
	A1.weightInKg = 20;
	A1.requiredLevel = 20;
	A1.compatibleClasses[0] = 8;

	unsigned int protValue = 3;
	CharacterStats modifiers;
	modifiers.currentHP = 300;
	modifiers.currentMP = -100;
	modifiers.AGI = 0;
	modifiers.DEF = 15;
	modifiers.INT = 0;
	modifiers.STR = 20;

	Item* second = new Armor(A1, protValue, modifiers);

	A1.name = "old relic";
	A1.rarity = Rarity::COMMON;
	A1.costInGoldCoins = 10;
	A1.weightInKg = 1;
	A1.requiredLevel = 1;
	A1.compatibleClasses[0] = 15;
	modifiers.currentHP = 10;
	modifiers.currentMP = 5;
	modifiers.AGI = 2;
	modifiers.DEF = 0;
	modifiers.INT = 2;
	modifiers.STR = 5;

	Item* third = new Relic(A1, modifiers);
	
	
	unsigned int hpModifier = 100;
	unsigned int mpModifier = 100;
	A1.name = "potion";
	A1.rarity = Rarity::COMMON;
	A1.costInGoldCoins = 10;
	A1.weightInKg = 0.5;
	A1.requiredLevel = 1;
	A1.compatibleClasses[0] = 15;
	StatusEffectType type1 = StatusEffectType::NONE;
	Item* fourth = new Consumable(A1, hpModifier, mpModifier, type1);
	

	std::ifstream file("testFile.bin", std::ios::binary);
	if (!file)
	{
		delete first;
		delete second;
		delete third;
		delete fourth;
		return 1;
	}

	uint32_t typeOfSpellValue = 0;
	file.read(reinterpret_cast<char*>(&typeOfSpellValue), sizeof(typeOfSpellValue));

	TypeOfSpell spellType = static_cast<TypeOfSpell>(typeOfSpellValue);
	Spell* spell = nullptr;
	switch (spellType)
	{
	case TypeOfSpell::DAMAGE:
		spell = new DamageSpell(file);
		break;
	case TypeOfSpell::HEAL:
		spell = new HealSpell(file);
		break;
	case TypeOfSpell::CLEANSE:
		spell = new CleanseSpell(file);
		break;
	default:
		break;
	}
	file.close();
	A1.name = "Ancient scroll";
	A1.rarity = Rarity::RARE;
	A1.costInGoldCoins = 100;
	A1.weightInKg = 0.5;
	A1.requiredLevel = 1;
	A1.compatibleClasses[0] = 14;


	Item* fifth = new Scroll(A1 , spell);

	std::ofstream file1("itemFile.bin", std::ios::binary);
	if (!file1)
	{
		delete first;
		delete second;
		delete third;
		delete fourth;
		delete fifth;
	}

	first->writeDataToFile(file1);
	second->writeDataToFile(file1);
	third->writeDataToFile(file1);
	fourth->writeDataToFile(file1);
	fifth->writeDataToFile(file1);

	file1.close();
	delete first;
	delete second;
	delete third;
	delete fourth;
	delete fifth;*/

	//std::string name("rado");
	//Hero* healer = new Healer(name);

	//std::string name1("petar");
	//Hero* mage = new Mage(name1);

	//std::string name2("anna");
	//Hero* warrior = new Warrior(name2);
	//
	//std::string name3("valieri");
	//Hero* paladin = new Paladin(name3);

	//std::string name4("skeleton");
	//Enemy* skeleton = new Skeleton(name4);

	//std::string name5("werewolf");
	//Enemy* werewolf = new Werewolf(name5);



	//delete healer;
	//delete mage;
	//delete warrior;
	//delete paladin;
	//delete skeleton;
	//delete werewolf;
	return 0;
}