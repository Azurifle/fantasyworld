#ifndef PLAYER
#define PLAYER
#pragma once
#include "Unit.hpp"

namespace G6037599
{
  class Player : public Unit
  {
  public:
    const char * WEAPON = "Fist !";
    static const int NONE = 0;
    const int MAX_HP, ATTACK_POWER = NONE;

    Player(World & t_world, int t_id, const char* t_name, int t_hp);
    Player(World& t_world, int t_id, const char* t_name, int t_hp
      , const char* t_weapon, int t_attack_power);

    const char* get_name() const override;
    void print_character() const override;
    void set_full_hp() override
      , update() override;
  protected:
    const char* get_attack_name() const override;
    int get_attack_power() const override;
    void dies() override;
  private:
    std::string m_name_{};
    bool m_has_long_gone_ = false;
  };
}

#endif //PLAYER
