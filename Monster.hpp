#ifndef MONSTER
#define MONSTER
#pragma once
#include "Unit.hpp"

namespace G6037599
{
	class Fantasy_world_2_d;

	class Monster: public Unit
	{
	public:
	  Monster(Fantasy_world_2_d& t_world, int t_id);

    void set_full_hp() override
      , update() override;
  protected:
    void damaged(int t_damage) override;

    virtual int get_max_hp() const = 0;
	};
}

#endif //MONSTER
