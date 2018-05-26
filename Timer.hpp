#ifndef TIMER
#define TIMER
#pragma once

namespace G6037599
{
  class Timer
  {
  public:
    const enum Enum { WIDTH = 22 };

    explicit Timer(const COORD& t_pos);
    ~Timer() = default;
    Timer(const Timer& t_to_copy);
    Timer& operator=(const Timer& t_to_copy);

    void show() const;
  private:
    COORD m_start_ = { 0, 0 };
    int m_day_ = 0, m_hour_ = 0, m_minute_ = 0;
  };
}//G6037599

#endif //TIMER