#include "stdafx.hpp"
#include "Player.hpp"

namespace G6037599
{
  //___ getter _________________________________________________
  const char* Player::get_name() const
  {
    return m_name_;
  }

  int Player::get_max_hp() const
  {
    return max_hp;
  }

  //___ (de)constructors _____________________________________________
  Player::Player(const char* t_name, const int t_hp): m_name_(t_name)
  {
    hp_ = max_hp = t_hp;
  }

  //___ public _______________________________________________________
  void Player::damaged(const int t_damage)
  {
    hp_ -= t_damage;
    std::cout << m_name_ << " received " << t_damage << " damages and now has " << hp_ << " health" << std::endl;
    if (hp_ <= 0)
    {
      std::cout << m_name_ << " say: ";
      switch (m_is_dead_)
      {
      case false: std::cout << "Ahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh, Sh*t I'm dead." << std::endl;
        m_is_dead_ = true;
        break;
      default: std::cout << "I'm already dead." << std::endl;
        break;
      }
    }//if (hp_ <= 0)
  }

  //___ public void const _________________________________________________
  void Player::print() const
  {
    std::cout << get_name() << ':' << hp_;
  }
}//G6037599
