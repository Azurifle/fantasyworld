#include "stdafx.h"
#include "Monster.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Monster::Monster(World& t_world, const int t_id) : Unit(t_world, t_id) {}

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
    case true: switch (is_near_target())
      {
      case true: attacks(); default:;
      } break;
    default: const auto SLOW_DYING = 1;
      damaged(SLOW_DYING);
    }//has_target
  }

  //___ protected _______________________________________________________
  void Monster::dies()
  {
    switch (has_target())
    {
    case true: std::cout << "I'll be back!"; default:;
    }
    respawn();
  }
}//G6037599