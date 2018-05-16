#include "stdafx.h"
#include "Zombie.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Zombie::Zombie(Fantasy_world_2_d& t_world, const int t_id): Monster(t_world, t_id) {} 
  
  //___ public _________________________________________________
  void Zombie::print_character() const
  {
    std::cout << 'Z';
  }

  //___ protected _________________________________________________
  const char* Zombie::get_name() const
  {
    return "Zombie";
  }

  const char* Zombie::get_attack_name() const
  {
    return "Bitting Attack !";
  }

  int Zombie::get_attack_power() const
  {
    const auto BASE_DAMAGE = 5, RANDOM_0_29 = 30;
    return BASE_DAMAGE + rand() % RANDOM_0_29;
  }

  int Zombie::get_max_hp() const
  {
    const auto ZOMBIE_MAX_HP = 2;
    return ZOMBIE_MAX_HP;
  }
}