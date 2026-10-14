#pragma once
#include "SystemState.h"
#include <string>
#include <vector>
class HeroManagerState: public SystemState
{
public:
	int display()override;
	SystemState* execute(int action)override;


private:
	void createNewhero(std::vector<std::string>& heroNames);
	void removeAHero(std::vector<std::string>& heroNames);

	static bool isBlank(const std::string& string);
	static bool doesHeroExist(const std::string& heroName , const std::vector<std::string>& heroNames);
	static std::string inputNewHeroName(const std::vector<std::string>& heroNames);

};

