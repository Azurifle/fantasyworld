#include "stdafx.h"
#include "Player.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Player::Player(World& t_world, const int t_id, const char* t_name, const int t_hp)
    : Unit(t_world, t_id), MAX_HP(t_hp)
  {
    m_name_ = '\"' + std::string(t_name) + '\"';
    set_hp(t_hp);
  }

  Player::Player(World& t_world, const int t_id
    , const char* t_name, const int t_hp, const char* t_weapon, const int t_attack_power)
    : Unit(t_world, t_id), WEAPON(t_weapon), MAX_HP(t_hp), ATTACK_POWER(t_attack_power)
  {
    m_name_ = '\"' + std::string(t_name) + '\"';
    set_hp(t_hp);
  }

  //___ public _________________________________________________
  const char* Player::get_name() const
  {
    return m_name_.c_str();
  }

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
    switch (has_target())
    {
    case true: switch (is_near_target())
      {
      case true: attacks(); break;
      default: clear_target();
      } break;
    default: break;
    }
  }

  //___ protected _______________________________________________________
  const char* Player::get_attack_name() const
  {
    return WEAPON;
  }

  int Player::get_attack_power() const
  {
    return ATTACK_POWER;
  }

  void Player::dies()
  {
    switch (m_has_long_gone_)
    {
    case false: std::cout << "Ahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh, Sh*t I'm dead.";
      m_has_long_gone_ = true;
      break;
    default: std::cout << "I'm already dead.";
    }
    game_reset();
  }

}//G6037599
