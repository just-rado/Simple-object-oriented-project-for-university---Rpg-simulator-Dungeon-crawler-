#pragma once
#include "SystemState.h"
class StateOnStart : public SystemState
{
public:
	int display()override;

	SystemState* execute(int action)override;


};

