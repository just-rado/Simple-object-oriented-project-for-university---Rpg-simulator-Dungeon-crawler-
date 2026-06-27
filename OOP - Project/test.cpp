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
#include "Room.h"
#include "Game.h"
#include "Dungeon.h"
#include "System.h"
int main()
{
	System system;
	// first dungeon - depths

	
	/*std::string nameOfRoom("Room2");

	std::string nameOfEnemy1("Skeli");
	Enemy* one = new Skeleton(nameOfEnemy1);

	std::string nameOfEnemy2("Propi");
	Enemy* two = new Skeleton(nameOfEnemy2);

	std::string nameOfEnemy3("BigBeast");
	Enemy* three = new Werewolf(nameOfEnemy3);

	std::vector<Enemy*> enemies;
	enemies.push_back(one);
	enemies.push_back(two);
	enemies.push_back(three);

	ItemData itemData;
	itemData.name = "meh weapon";
	itemData.rarity = Rarity::LEGENDARY;
	itemData.costInGoldCoins = 100;
	itemData.weightInKg = 10;
	itemData.requiredLevel = 10;
	itemData.compatibleClasses.push_back(1);

	AugmentationType type = AugmentationType::HOLY;
	unsigned int dmgVal = 1000;
	unsigned int criticalChance = 100;

	Item* first = new Weapon(itemData, type, dmgVal, criticalChance);

	std::vector<Item*> items;
	items.push_back(first);


	Room* room1 = new Room(nameOfRoom, enemies, items);



	delete one;
	delete two;
	delete three;
	delete first;

	std::string dungeonName("depths");

	Dungeon dungeon1(dungeonName, room1);

	std::ofstream file(dungeonName, std::ios::binary | std::ios::app);
	if (!file.is_open())
	{
		delete room1;
		return 1;
	}
	
	dungeon1.writeCurrentRoomToFile(file);

	file.close();
	delete room1;*/
	

	//std::ifstream heroFile("heroFile.bin", std::ios::binary);
	//if (!heroFile.is_open())
	//{
	//	return 1;
	//}

	//Hero* heroes[4]{};

	//for (size_t i = 0; i < 4; ++i)
	//{
	//	uint32_t heroTypeValue = 0;
	//	
	//	heroFile.read(reinterpret_cast<char*>(&heroTypeValue), sizeof(heroTypeValue));
	//	
	//	HeroClass type = static_cast<HeroClass>(heroTypeValue);
	//	switch (type)
	//	{
	//	case HeroClass::WARRIOR:
	//		heroes[i] = new Warrior(heroFile);
	//		break;
	//	case HeroClass::MAGE:
	//		heroes[i] = new Mage(heroFile);
	//		break;
	//		
	//	case HeroClass::HEALER:
	//		heroes[i] = new Healer(heroFile);
	//		break;
	//	case HeroClass::PALADIN:
	//		heroes[i] = new Paladin(heroFile);
	//		break;
	//	case HeroClass::NUM_CLASSES:
	//		std::cout << "why\n";
	//		break;
	//	default:
	//		break;
	//	}
	//	
	//}
	//heroFile.close();

	//for (size_t i = 0; i < 4; ++i)
	//{
	//	if (!heroes[i])
	//	{
	//		continue;
	//	}
	//	if (heroes[i]->getItemFromInvetoryAtIndex(0))
	//	{
	//		std::cout << heroes[i]->getItemFromInvetoryAtIndex(0)->getName() << '\n';
	//	}
	//	if (heroes[i]->getItemFromInvetoryAtIndex(1))
	//	{
	//		std::cout << heroes[i]->getItemFromInvetoryAtIndex(1)->getName() << '\n';
	//	}
	//	
	//	delete heroes[i];
	//}

	//std::ifstream enemyFile("enemyFile.bin", std::ios::binary);
	//if (!enemyFile.is_open())
	//{
	//	return 1;
	//}

	//Enemy* enemies[2]{};

	//for (size_t i = 0; i < 2; ++i)
	//{
	//	uint32_t enemyTypeValue = 0;

	//	enemyFile.read(reinterpret_cast<char*>(&enemyTypeValue), sizeof(enemyTypeValue));

	//	TypeOfEnemy type = static_cast<TypeOfEnemy>(enemyTypeValue);

	//	switch (type)
	//	{
	//	case TypeOfEnemy::SKELETON:
	//		enemies[i] = new Skeleton(enemyFile);
	//		break;
	//	case TypeOfEnemy::WEREWOLF:
	//		enemies[i] = new Werewolf(enemyFile);
	//		break;
	//	default:
	//		break;
	//	}
	//}

	//enemyFile.close();

	//for (size_t i = 0; i < 2; ++i)
	//{
	//	if (!enemies[i])
	//	{
	//		continue;
	//	}

	//	std::cout << enemies[i]->getName() << '\n';
	//	delete enemies[i];
	//}

	/*std::ifstream file("itemFile.bin", std::ios::binary);
	if (!file.is_open())
	{
		return 1;
	}
	
	Item* items[5]{};
	for (size_t i = 0; i < 5; ++i)
	{
		uint32_t itemTypeValue = 0;
		file.read(reinterpret_cast<char*>(&itemTypeValue), sizeof(itemTypeValue));
		uint64_t id = 0;
		file.read(reinterpret_cast<char*>(&id), sizeof(id));

		TypeOfItem type = static_cast<TypeOfItem>(itemTypeValue);
		switch (type)
		{
		case TypeOfItem::WEAPON:
			items[i] = new Weapon(file, id);
			break;
		case TypeOfItem::ARMOR:
			items[i] = new Armor(file, id);
			break;
		case TypeOfItem::CONSUMABLE:
			items[i] = new Consumable(file, id);
			break;
		case TypeOfItem::SCROLL:
			items[i] = new Scroll(file, id);
			break;
		case TypeOfItem::RELIC:
			items[i] = new Relic(file, id);
			break;
		default:
			std::cout << "nay" << " " << i;
			break;
		}
	}
	file.close();

	std::string name("rado");
	Hero* healer = new Healer(name);

	std::string name1("petar");
	Hero* mage = new Mage(name1);

	std::string name2("anna");
	Hero* warrior = new Warrior(name2);

	std::string name3("valieri");
	Hero* paladin = new Paladin(name3);

	std::string name4("skeleton");
	Enemy* skeleton = new Skeleton(name4);

	std::string name5("werewolf");
	Enemy* werewolf = new Werewolf(name5);

	paladin->collectItem(items[0]);
	paladin->collectItem(items[1]);
	
	warrior->collectItem(items[4]);
	mage->collectItem(items[3]);

	Skeleton* sk = static_cast<Skeleton*>(skeleton);
	sk->addItem(items[2]);

	healer->collectItem(items[2]);
	

	for (size_t i = 0; i < 5; ++i)
	{
	
		delete items[i];
	
	}

	std::ofstream heroFile("heroFile.bin", std::ios::binary);
	if (!heroFile.is_open())
	{
		delete healer;
		delete mage;
		delete warrior;
		delete paladin;
		delete skeleton;
		delete werewolf;
		return 1;
	}

	healer->writeToFile(heroFile);
	paladin->writeToFile(heroFile);
	warrior->writeToFile(heroFile);
	mage->writeToFile(heroFile);
	heroFile.close();

	std::ofstream enemyFile("enemyFile.bin", std::ios::binary);
	if (!enemyFile.is_open())
	{
		delete healer;
		delete mage;
		delete warrior;
		delete paladin;
		delete skeleton;
		delete werewolf;
		return 1;
	}

	skeleton->writeToFile(enemyFile);
	werewolf->writeToFile(enemyFile);
	enemyFile.close();

	delete healer;
	delete mage;
	delete warrior;
	delete paladin;
	delete skeleton;
	delete werewolf;*/

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

	
	return 0;
}