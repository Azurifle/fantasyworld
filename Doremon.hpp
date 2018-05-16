#ifndef DOREMON
#define DOREMON
#pragma once
#include "Monster.hpp"

namespace G6037599
{
  class Doremon : public Monster
  {
  public:
    Doremon(Fantasy_world_2_d& t_world, const int t_id);

    void print_character() const override;
  protected:
    const char* get_name() const override
      , * get_attack_name() const override;
    int get_attack_power() const override
      , get_max_hp() const override;
  };
}
#endif //DOREMON