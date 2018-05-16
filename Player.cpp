#include "stdafx.h"
#include "Player.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Player::Player(Fantasy_world_2_d& t_world, const int t_id, const char* t_name, const int t_hp)
    : Unit(t_world, t_id), NAME(t_name), MAX_HP(t_hp)
  {
    set_hp(t_hp);
  }

  Player::Player(Fantasy_world_2_d& t_world, const int t_id
    , const char* t_name, const int t_hp, const char* t_weapon, const int t_attack_power)
    : Unit(t_world, t_id), NAME(t_name), WEAPON(t_weapon), MAX_HP(t_hp), ATTACK_POWER(t_attack_power)
  {
    set_hp(t_hp);
  }

  //___ public _________________________________________________
  void Player::print_character() const
  {
    std::cout << '&';
  }

  void Player::set_full_hp()
  {
    set_hp(MAX_HP);
  }

  void Player::update()
  {
    if (has_target())
      attacks();
  }

  //___ protected _______________________________________________________
  const char* Player::get_name() const
  {
    return NAME;
  }

  const char* Player::get_attack_name() const
  {
    return WEAPON;
  }

  int Player::get_attack_power() const
  {
    return ATTACK_POWER;
  }

  void Player::damaged(const int t_damage)
  {
    set_hp(get_hp() - t_damage);
    std::cout << NAME << " -" << t_damage << " damage. Now has " << get_hp() << " health."
      << std::endl;
    if (get_hp() <= DEAD)
    {
      std::cout << NAME << " say: ";
      switch (m_has_long_gone_)
      {
      case false: std::cout << "Ahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh, Sh*t I'm dead." << std::endl;
        m_has_long_gone_ = true;
        break;
      default: std::cout << "I'm already dead." << std::endl;
        break;
      }
    }//is dead
    puts("");
  }

}//G6037599
