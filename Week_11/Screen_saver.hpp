#ifndef G6037599_SCREEN_SAVER_MENU_HPP
#define G6037599_SCREEN_SAVER_MENU_HPP
#pragma once
#include "Delta_time.hpp"

namespace G6037599
{
  class Star;

  class Screen_saver final
  {
  public:
    static void run();
  private:
    static Screen_saver m_instance_;

    static GLFWwindow* glfw_window();
    static void key_callback(GLFWwindow* t_window, int t_key, int t_scan_code, int t_action, int t_mods);
    static void render_background();

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

#endif //G6037599_SCREEN_SAVER_MENU_HPP
