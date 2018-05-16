#include "stdafx.h"
#include "Orc.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Orc::Orc(Fantasy_world_2_d& t_world, const int t_id): Monster(t_world, t_id) {}

  //___ public _________________________________________________
  void Orc::print_character() const
  {
    std::cout << 'O';
  }

  //___ protected _________________________________________________
  const char* Orc::get_name() const
  {
    return "Orc";
  }

  const char* Orc::get_attack_name() const
  {
    return "Orc Slash !";
  }

  int Orc::get_attack_power() const
  {
    const auto BASE_DAMAGE = 25, RANDOM_0_24 = 25;
    return BASE_DAMAGE + rand() % RANDOM_0_24;
  }

  int Orc::get_max_hp() const
  {
    const auto ORC_MAX_HP = 5;
    return ORC_MAX_HP;
  }
}