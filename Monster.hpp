#ifndef MONSTER
#define MONSTER
#pragma once
#include "Unit.hpp"

namespace G6037599
{
	class World;

	class Monster: public Unit
	{
	public:
	  Monster(World& t_world, int t_id);

    void set_full_hp() override
      , update() override;
  protected:
    void dies() override;

    virtual int get_max_hp() const = 0;
	};
}

#endif //MONSTER
