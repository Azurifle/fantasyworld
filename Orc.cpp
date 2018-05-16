#include "stdafx.h"
#include "Orc.hpp"

namespace G6037599
{
  //___ public const _________________________________________________
  const char* Orc::get_attack_name() const
  {
    return "Orc Slash !";
  }

  const char* Orc::get_name() const
  {
    return "Orc";
  }

  int Orc::get_attack_damage() const
  {
    const auto BASE_DAMAGE = 25, RANDOM_0_24 = 25;
    return BASE_DAMAGE + rand() % RANDOM_0_24;
  }

  char Orc::get_type() const
  {
    return 'o';
  }

  int Orc::get_max_hp() const
  {
    const auto ORC_MAX_HP = 5;
    return ORC_MAX_HP;
  }
}