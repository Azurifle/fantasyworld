#ifndef MONSTER
#define MONSTER
#pragma once
#include "fantasy_world_2_d.h"

class fantasy_world_2_d;

class monster
{
public:
	static const int MAX_HP = 3;

	monster() = default;
	explicit monster(int id, fantasy_world_2_d* world);
	virtual ~monster() = default;

	void print() const;
	void update();
	void respawn(int x, int y);
private:
	fantasy_world_2_d* world_ = nullptr;
	int id_ = -1, hp_ = -1, x_ = -1, y_ = -1;
};

#endif //MONSTER
