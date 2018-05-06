#ifndef MONSTER
#define MONSTER
#pragma once
#include "player.h"
class monster
{
public:
	monster();
	virtual ~monster();

	void set_target(player* target);
	virtual void on_update() const;

protected:
	player* target_ = nullptr;
	const char* name_ = nullptr;
	int damage_ = 0;
};

#endif //MONSTER
