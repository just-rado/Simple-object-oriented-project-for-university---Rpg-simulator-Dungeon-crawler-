#pragma once
#include "SystemState.h"
#include "Hero.h"
#include <string>
#include <vector>
class HeroesState: public SystemState
{
public:
	HeroesState(const std::vector<std::string>& heroNames);

	int display()override;
	SystemState* execute(int action)override;


private:
	static Hero* loadHeroData(const std::string& name);

	static void heroInfo(const std::vector<std::string>& heroNames);

	static void storeHeroData(const Hero* hero);

	static void giveItem(Hero* giver, Hero* reciever);

	static void SwitchItemsBetweenTwoHeroes(const std::string& firstHeroName, const std::string& secondHeroName);

	static void manageItemsOfASingleHero(const std::string& heroName);

	static void manageItems(const std::vector<std::string>& heroNames);

	static TypeOfItem chooseItemType();

	static int InputItemID(); // assume that item id wont get bigger than int :)

	static int InputItemSlot();

};

