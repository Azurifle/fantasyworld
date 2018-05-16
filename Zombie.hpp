#ifndef ZOMBIE
#define ZOMBIE
#pragma once
#include "Monster.hpp"

namespace G6037599
{
  class Zombie : public Monster
  {
  public:
    Zombie(Fantasy_world_2_d& t_world, int t_id);

    void print_character() const override;
  protected:
    const char* get_name() const override
      , * get_attack_name() const override;
    int get_attack_power() const override
      , get_max_hp() const override;    
  };
}
#endif //ZOMBIE