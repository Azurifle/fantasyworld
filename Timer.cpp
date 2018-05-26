#include "stdafx.h"
#include "Timer.hpp"
#include "Console.hpp"

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Timer::Timer(const COORD& t_pos) : m_start_(t_pos) {}

  Timer::Timer(const Timer& t_to_copy)
  {
    m_start_ = t_to_copy.m_start_;
    m_day_ = t_to_copy.m_day_;
    m_hour_ = t_to_copy.m_hour_;
    m_minute_ = t_to_copy.m_minute_;
  }

  Timer& Timer::operator=(const Timer& t_to_copy)
  {
    m_start_ = t_to_copy.m_start_;
    m_day_ = t_to_copy.m_day_;
    m_hour_ = t_to_copy.m_hour_;
    m_minute_ = t_to_copy.m_minute_;
    return *this;
  }

  //___ public _______________________________________________________
  void Timer::show() const
  {
    Console::set_cursor(m_start_);
    std::cout << std::setw(WIDTH) << std::setfill('=');

    enum Enum
    {
      ROW_TIME = 1, ROW_BOTTOM, DAY_FIELD_WIDTH = 4, HOUR_FIELD_WIDTH = 2
    };
    Console::set_cursor({m_start_.X, m_start_.Y+ ROW_TIME });
    std::cout << "| " << std::setw(DAY_FIELD_WIDTH) << std::setfill('0') 
      << m_day_ << " Day " << std::setw(HOUR_FIELD_WIDTH) << std::setfill('0')
      << m_hour_ << ':' << m_minute_ << " Hour |";

    Console::set_cursor({ m_start_.X, m_start_.Y + ROW_BOTTOM });
    std::cout << std::setw(WIDTH) << std::setfill('=');
  }
}//G6037599