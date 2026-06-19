#include "Mage.h"

Mage::Mage(const std::string& name): Hero(createMageData(name) , HERO_CLASS) , spells()
{

}
Mage::Mage(const Mage& other): Hero(other)
{
	deepCopySpells(other.spells);
}
Mage& Mage::operator=(const Mage& other)
{
	if (this != &other)
	{
		Mage temp(other);
		swap(temp);
	}
	return *this;
}
Mage::~Mage()
{
	free(this->spells);
}


void Mage::swap(Mage& other)noexcept
{

}
	 
void Mage::deepCopySpells(const std::vector<Spell*> spells)
{
	std::vector<Spell*> toDelete = std::move(this->spells);
	try
	{
		this->spells.clear();
		size_t size = spells.size();
		for (size_t i = 0; i < size; ++i)
		{
			this->spells.push_back(spells[i]->clone());
		}
	}
	catch (...)
	{
		free(this->spells);
		this->spells = std::move(toDelete);
	}
	free(toDelete);
}
void Mage::free(std::vector<Spell*>& spells)
{
	size_t size = spells.size();
	for (size_t i = 0; i < size; ++i)
	{
		delete spells[i];
	}
	spells.clear();
}
