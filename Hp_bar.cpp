#include "stdafx.h"
#include "Hp_bar.hpp"
#include "Console.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Hp_bar::Hp_bar(const COORD& t_pos) : m_start_(t_pos) {}

  Hp_bar::Hp_bar(const Hp_bar& t_to_copy)
  {
    m_start_ = t_to_copy.m_start_;
    m_hp_ = t_to_copy.m_hp_;
    m_max_hp_ = t_to_copy.m_max_hp_;
  }

  Hp_bar& Hp_bar::operator=(const Hp_bar& t_to_copy)
  {
    m_start_ = t_to_copy.m_start_;
    m_hp_ = t_to_copy.m_hp_;
    m_max_hp_ = t_to_copy.m_max_hp_;
    return *this;
  }

  void Hp_bar::show() const
  {
    Console::set_cursor(m_start_);
    std::cout << '[';
    const auto MAX_BAR = 6;
    auto bar_left = MAX_BAR * m_hp_ / m_max_hp_;

    bar_left = print_half_bar(bar_left);

    std::cout << "HP:" << m_hp_ << '/' << m_max_hp_;

    print_half_bar(bar_left);

    std::cout << ']';
  }

  //___ public _____________________________________________
  void Hp_bar::increase_max(const int t_increase)
  {
    const auto HP_DISPLAY_LIMIT = 999;
    REQUIRE(0 < t_increase && m_max_hp_+t_increase <= HP_DISPLAY_LIMIT);

    m_max_hp_ += t_increase;
    m_hp_ += t_increase;
  }

  COORD Hp_bar::get_pos() const
  {
    return m_start_;
  }

  //___ private static _____________________________________________
  int Hp_bar::print_half_bar(int t_bar_left)
  {
    const enum Bar {NO_BAR, BAR_1, HALF_BAR = 3};
    for (int i = BAR_1; i <= HALF_BAR; ++i)
    {
      if (t_bar_left > NO_BAR)
      {
        std::cout << '|';
        --t_bar_left;
      }
      else
      {
        std::cout << ' ';
      }
    }

    return t_bar_left;
  }

}//G6037599
