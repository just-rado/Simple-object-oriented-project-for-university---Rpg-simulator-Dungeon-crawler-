#include "HeroesState.h"
#include <iostream>
#include "HeroFactory.h"
#include "Item.h"
#include "SafeInputReading.h"
#include <fstream>
#include "StringHelpers.h"

HeroesState::HeroesState(const std::vector<std::string>& heroNames)
{
	while (true)
	{
		std::cout << "Choose\n";
		std::cout << "1.Show information of a particular hero\n";
		std::cout << "2.Manage items\n";
		std::cout << "3.Back\n";
		int action = 0;
		if (!readValidInt(1, 3, action))
		{
			if (!tryAgain("Wrong input"))
			{
				break;
			}
			else
			{
				continue;
			}
		}

		switch (action)
		{
		case 1:
			heroInfo(heroNames);
			continue;
		case 2:
			manageItems(heroNames);
			continue;
		case 3:
			break;
		default:
			break;
		}
	}
}
int HeroesState::display()
{
	return 1;
}

SystemState* HeroesState::execute(int action)
{
	return nullptr;
}

Hero* HeroesState::loadHeroData(const std::string& name)
{
	std::ifstream heroFile(name, std::ios::binary);
	if (!heroFile.is_open())
	{
		return nullptr;
	}

	uint32_t heroClassValue = 0;
	heroFile.read(reinterpret_cast<char*>(&heroClassValue), sizeof(heroClassValue));

	HeroClass type = static_cast<HeroClass>(heroClassValue);

	Hero* toStore = HeroFactory::loadHeroFromFile(heroFile, type);
	heroFile.close();

	if (!toStore)
	{
		return nullptr;;
	}

	return toStore;
}

void HeroesState::heroInfo(const std::vector<std::string>& heroNames)
{
	std::string nameOfHero = getString("name of hero");

	size_t size = heroNames.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (heroNames[i] == nameOfHero)
		{
			Hero* hero = loadHeroData(nameOfHero);

			if (hero)
			{
				// in hero add a function that prints the information of the hero
				delete hero;
			}
			else
			{
				std::cout << "Failed to load hero data" << "\n\n\n";
			}

			return;
		}
	}
	std::cout << "No hero with that name exists" << "\n\n\n";
}

void HeroesState::SwitchItemsBetweenTwoHeroes(const std::string& firstHeroName, const std::string& secondHeroName)
{
	Hero* firstHero = loadHeroData(firstHeroName);
	if (!firstHero)
	{
		std::cout << "Could not load first hero's data\n\n\n";
		return;
	}
	Hero* secondHero = loadHeroData(secondHeroName);
	if (!secondHero)
	{
		delete firstHero;
		std::cout << "Could not load second hero's data\n\n\n";
		return;
	}

	while (true)
	{
		std::cout << "Choose which hero receives item\n";
		std::cout << "1.First hero\n";
		std::cout << "2.Second hero\n";

		int action = 0;
		if (!readValidInt(1, 2, action))
		{
			if (!tryAgain("Wrong input"))
			{
				storeHeroData(firstHero);
				delete firstHero;

				storeHeroData(secondHero);
				delete secondHero;
				return;
			}
			else
			{
				continue;
			}
		}

		switch (action)
		{
		case 1:
			giveItem(secondHero, firstHero);
			break;
		case 2:
			giveItem(firstHero, secondHero);
			break;
		}

		std::cout << "Continue exchanging items?\n";
		std::cout << "1.Yes\n";
		std::cout << "2.No\n";

		if (!readValidInt(1, 1, action))
		{
			storeHeroData(firstHero);
			delete firstHero;

			storeHeroData(secondHero);
			delete secondHero;

			return;
		}
	}
}

void HeroesState::manageItemsOfASingleHero(const std::string& heroName)
{
	Hero* hero = loadHeroData(heroName);
	if (!hero)
	{
		std::cout << "Could not load hero data\n\n\n";
		return;
	}

	while (true)
	{
		std::cout << "Chose option:\n";
		std::cout << "1.Show all equipped items\n";
		std::cout << "2.Show items in inventory\n";
		std::cout << "3.Show all items of particular type\n";
		std::cout << "4.Equip an item from inventory\n";
		std::cout << "5.Unequip item\n";
		std::cout << "6.Back\n";

		int action = 0;
		if (!readValidInt(1, 6, action))
		{
			if (!tryAgain("Wrong input"))
			{
				storeHeroData(hero);
				delete hero;
				return;
			}
			else
			{
				continue;
			}
		}

		switch (action)
		{
		case 1:
			hero->printEquippedItems();
			continue;
		case 2:
			hero->printItemsFromInventory();
			continue;
		case 3:
			hero->printItemsOfParticularType(chooseItemType());
			continue;
		case 4:
			if(!hero->equipItem(InputItemID()))
			{
				std::cout << "Could not equip\n";
			}
			continue;
		case 5:
			if (!hero->unequipItem(InputItemSlot()))
			{
				std::cout << "Could not unequip\n";
				continue;
			}
		case 6:
			storeHeroData(hero);
			delete hero;
			return;
		}


	}

}

void HeroesState::manageItems(const std::vector<std::string>& heroNames)
{
	std::cout << "1.Manage items of a single hero\n";
	std::cout << "2.Manage items between two heroes\n";

	int command = 0;
	std::cin >> command;
	if (command == 1)
	{
		std::string heroName = getString("name of hero");

		if (doesStringExist(heroName , heroNames))
		{
			manageItemsOfASingleHero(heroName);
		}
		else
		{
			"Hero with this name does not exist\n\n\n";
		}

	}
	else if (command == 2)
	{
		std::string firstHeroName = getString("name of first hero");
		std::string secondHeroName = getString("name of second hero");

		if (firstHeroName == secondHeroName)
		{
			return;
		}

		bool firstExists = false;
		bool secondExists = false;

		size_t size = heroNames.size();
		for (size_t i = 0; i < size; ++i)
		{
			if (!firstExists && areEqual(heroNames[i],firstHeroName))
			{
				firstExists = true;
			}
			else if (!secondExists && areEqual(heroNames[i] , secondHeroName))
			{
				secondExists = true;
			}

			if (firstExists && secondExists)
			{
				break;
			}
		}

		if (!firstExists || !secondExists)
		{
			std::cout << "Could not find heroes with those names\n\n\n";
			return;
		}

		SwitchItemsBetweenTwoHeroes(firstHeroName, secondHeroName);
	}
}


TypeOfItem HeroesState::chooseItemType()
{
	while (true)
	{
		std::cout << "Choose Item type:\n";
		Item::printItemTypes();

		int type = -1;
		if (!readValidInt(0, Item::numberOfItemTypes(), type))
		{
			std::cout << "Invalid\n";
			continue;
		}

		return Item::convertIntToItemType(type);
	}
	
}

int HeroesState::InputItemID()
{
	while (true)
	{
		std::cout << "Give item ID\n";
		int ID = 0;

		if (!readValidInt(0, INT_MAX, ID))
		{
			std::cout << "Invalid\n";
			continue;
		}

		return ID;
	}
}

int HeroesState::InputItemSlot()
{
	while (true)
	{
		size_t cap = Hero::getCapacityForEquippedItems();
		if (cap == 0)
		{
			return 0;
		}

		std::cout << "Give item slot\n";
		std::cout << "Number of slots are " << cap << "\n";
		std::cout << "Starting from 0\n";
		int slot = 0;

		if (!readValidInt(0, cap - 1, slot))
		{
			std::cout << "Invalid\n";
			continue;
		}

		return slot;
	}
}

void HeroesState::storeHeroData(const Hero* hero)
{
	std::ofstream store(hero->getName(), std::ios::binary);
	if (store.is_open())
	{
		hero->writeToFile(store);
		store.close();
	}
	else
	{
		std::cout << "Could not store data\n\n\n";
	}
}

void HeroesState::giveItem(Hero* giver, Hero* reciever)
{
	std::cout << "Giver's inventory:\n";
	giver->printItemsFromInventory();
	std::cout << "Pick item to give:\n";
	Item* toGive = giver->dropItemFromInventory(InputItemID());

	if (!reciever->collectItem(toGive))
	{
		std::cout << "Could not give item\n";
		giver->collectItem(toGive);
	}
}



