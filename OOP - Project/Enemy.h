#pragma once
#include "Character.h"
class Enemy: public Character
{
public:
	virtual Enemy* clone()const = 0;
private:

};

