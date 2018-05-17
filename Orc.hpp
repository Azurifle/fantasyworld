#ifndef ORC
#define ORC
#pragma once
#include "Monster.hpp"

namespace G6037599
{
  class Orc : public Monster
  {
  public:
    Orc(World& t_world, const int t_id);

    const char* get_name() const override;
    void print_character() const override;
  protected:
    const char* get_attack_name() const override;
    int get_attack_power() const override
      , get_max_hp() const override;
  };
}
#endif //ORC
