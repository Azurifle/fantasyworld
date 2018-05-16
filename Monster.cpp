#include "stdafx.h"
#include "Monster.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Monster::Monster(Fantasy_world_2_d& t_world, const int t_id) : Unit(t_world, t_id) {}

  //___ public _____________________________________________
  void Monster::set_full_hp()
  {
    const auto RANDOM_0_1 = 2;
    set_hp(get_max_hp() + rand() % RANDOM_0_1);

    PROMISE(get_hp() > DEAD);
  }

  void Monster::update()
  {
    switch (has_target())
    {
    case true: if (is_near_target())
      {
        attacks();
      }
      break;
    default: const auto SLOW_DYING = 1;
      damaged(SLOW_DYING);
    }
  }

  //___ protected _______________________________________________________
  void Monster::damaged(const int t_damage)
  {
    set_hp(get_hp() - t_damage);
    if(get_hp() <= DEAD)
    {
      respawn();
    }
  }
}//G6037599