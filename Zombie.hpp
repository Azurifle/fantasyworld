#ifndef ZOMBIE
#define ZOMBIE
#pragma once
#include "Monster.hpp"

namespace G6037599
{
  class Zombie : public Monster
  {
  public:
    const char* get_attack_name() const override;
    const char* get_name() const override;
    int get_attack_damage() const override;
    char get_type() const override;
    int get_max_hp() const override;

    Zombie(Fantasy_world_2_d& t_world, const int t_id) : Monster(t_world, t_id) {}
  };
}
#endif //ZOMBIE