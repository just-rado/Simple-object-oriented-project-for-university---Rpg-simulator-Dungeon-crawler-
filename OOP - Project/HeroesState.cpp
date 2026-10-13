#include "HeroesState.h"
#include <iostream>
#include "HeroFactory.h"
#include "Item.h"
#include "SafeInputReading.h"


bool  HeroesState::doesHeroExist(const std::string& name , const std::vector<std::string>& heroNames)
{
	size_t size = heroNames.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (heroNames[i] == name)
		{
			return true;
		}
	}
	return false;
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

void HeroesState::heroInfo(const std::string& heroName , const std::vector<std::string>& heroNames)
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

		if (doesHeroExist(heroName , heroNames))
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
			if (!firstExists && heroNames[i] == firstHeroName)
			{
				firstExists = true;
			}
			else if (!secondExists && heroNames[i] == secondHeroName)
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