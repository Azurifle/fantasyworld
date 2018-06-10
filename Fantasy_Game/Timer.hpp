#ifndef TIMER
#define TIMER
#pragma once

namespace G6037599
{
  class Timer
  {
  public:
    const enum Enum { NOT_REACH, HOUR_REACH, DAY_REACH, ROW_TIME = 1, ROW_BOTTOM
      , HOUR_FIELD_WIDTH = 2, DAY_FIELD_WIDTH = 4, WIDTH = 22 
      , DAY_FIELD_X = 2, HOUR_FIELD_X = 11, MINUTE_FIELD_X = 14};

    explicit Timer(const COORD& t_pos);
    ~Timer() = default;
    Timer(const Timer& t_to_copy) = default;//no (smart)pointer
    Timer& operator=(const Timer& t_to_copy) = default;

    void show();
    int update_minute();
    int update_hour();
  private:
    COORD m_start_ = { 0, 0 };
    int m_day_ = 1, m_hour_ = 0, m_minute_ = 0;
  };
}//G6037599

#endif //TIMER