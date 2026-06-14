#pragma once
#include "Item.h"
#include "Enemy.h"
#include <string>
#include <vector>
class Room
{
public:
	Room(const std::string& name, const std::vector<Enemy*>& enemies, const std::vector<Item*>& items);
	Room(const Room& other);
	Room& operator=(const Room& other) = delete;
	~Room();

	size_t getNumberOfEnemies()const;
	size_t getNumberOfItems()const;

	Enemy& getEnemy(size_t index)const;
	Item& getItem(size_t index)const;

	bool isEmpty()const;

private:
	const std::string name;
	std::vector<Enemy*> enemies;
	std::vector<Item*> items;

	void handleHeapMemory(const std::vector<Enemy*>& enemies , const std::vector<Item*>& items);
	
	template<typename T>
	void deleteVectorPointers(std::vector<T*>& vec);
};

template<typename T>
void Room::deleteVectorPointers(std::vector<T*>& ptrContainer)
{
	size_t size = ptrContainer.size();
	for (size_t i = 0; i < size; ++i)
	{
		delete ptrContainer[i];
	}
	ptrContainer.clear();
}

	