#ifndef G6037599_SCREEN_SAVER_HPP
#define G6037599_SCREEN_SAVER_HPP
#pragma once
#include "Delta_time.hpp"

namespace G6037599
{
  class Star;

  class Screen_saver final
  {
  public:
    static void start();
  private:
    static Screen_saver m_instance_;

    Delta_time m_delta_time_;
    std::vector<Star> m_stars_{};

    Screen_saver();
    ~Screen_saver() = default;
    Screen_saver(const Screen_saver& t_to_copy) = default;
    Screen_saver(Screen_saver&& t_to_move) noexcept = default;
    Screen_saver& operator = (const Screen_saver& t_to_copy) = default;
    Screen_saver& operator = (Screen_saver&& t_to_move) noexcept = default;

    void update();
  };
}//G6037599

#endif //G6037599_SCREEN_SAVER_HPP
