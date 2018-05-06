#ifndef ZOMBIE
#define ZOMBIE
#pragma once
#include "monster.h"

class zombie : public monster
{
public:
	zombie();
	//use monster deconstructor
	void on_update() const override;
};

#endif //ZOMBIE