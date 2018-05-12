#pragma once
#include "monster.h"

class player : monster
{
public:
	player(const char* name, int hp);
	virtual ~player();

private:
	bool is_dead_ = false;
};

