#include "stdafx.h"
#include "Doremon.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Doremon::Doremon(Fantasy_world_2_d& t_world, const int t_id): Monster(t_world, t_id) {} 
  
  //___ public _________________________________________________
  void Doremon::print_character() const
  {
    std::cout << 'D';
  }

  //___ protected _________________________________________________
  const char* Doremon::get_name() const
  {
    return "Doremon";
  }

  const char* Doremon::get_attack_name() const
  {
    return "Magical Device Attack !!";
  }
  
  int Doremon::get_attack_power() const
  {
    const auto BASE_DAMAGE = 50, RANDOM_0_4 = 5;
    return BASE_DAMAGE + rand() % RANDOM_0_4;
  }

  int Doremon::get_max_hp() const
  {
    const auto DOREMON_MAX_HP = 8;
    return DOREMON_MAX_HP;
  }
}