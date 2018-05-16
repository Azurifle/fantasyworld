#include "stdafx.h"
#include "Zombie.hpp"

namespace G6037599
{
  //___ public const _________________________________________________
  const char* Zombie::get_attack_name() const
  {
    return "Bitting Attack !";
  }

  const char* Zombie::get_name() const
  {
    return "Zombie";
  }

  int Zombie::get_attack_damage() const
  {
    const auto BASE_DAMAGE = 5, RANDOM_0_29 = 30;
    return BASE_DAMAGE + rand() % RANDOM_0_29;
  }

  char Zombie::get_type() const
  {
    return 'z';
  }

  int Zombie::get_max_hp() const
  {
    const auto ZOMBIE_MAX_HP = 2;
    return ZOMBIE_MAX_HP;
  }
}