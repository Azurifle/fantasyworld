#include "stdafx.h"
#include "Doremon.hpp"

namespace G6037599
{
  //___ public const _________________________________________________
  const char* Doremon::get_attack_name() const
  {
    return "Magical Device Attack !!";
  }

  const char* Doremon::get_name() const
  {
    return "Doremon";
  }

  int Doremon::get_attack_damage() const
  {
    const auto BASE_DAMAGE = 50, RANDOM_0_4 = 5;
    return BASE_DAMAGE + rand() % RANDOM_0_4;
  }

  char Doremon::get_type() const
  {
    return 'd';
  }

  int Doremon::get_max_hp() const
  {
    return 8;
  }
}