#ifndef PLAYER
#define PLAYER
#pragma once
#include "Unit.hpp"

namespace G6037599
{
  class Player : public Unit
  {
  public:
    const char * NAME, * WEAPON = "Fist !";
    static const int NONE = 0;
    const int MAX_HP, ATTACK_POWER = NONE;

    Player(Fantasy_world_2_d & t_world, int t_id, const char* t_name, int t_hp);
    Player(Fantasy_world_2_d& t_world, int t_id, const char* t_name, int t_hp
      , const char* t_weapon, int t_attack_power);

    void print_character() const override;
    void set_full_hp() override
      , update() override;
  protected:
    const char* get_name() const override
      , * get_attack_name() const override;
    int get_attack_power() const override;
    void damaged(int t_damage) override;
  private:
    bool m_has_long_gone_ = false;
  };
}

#endif //PLAYER
