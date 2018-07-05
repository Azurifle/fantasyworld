#ifndef G6037599_SCREEN_SAVER_MENU_HPP
#define G6037599_SCREEN_SAVER_MENU_HPP
#pragma once
#include "Week_09/Vec3.hpp"

namespace G6037599
{
  class Screen_saver final
  {
  public:
    static void run();
  private:
    static GLFWwindow* glfw_window();
    static void key_callback(GLFWwindow* t_window, int t_key, int t_scan_code, int t_action, int t_mods);

    Screen_saver() = default;
    ~Screen_saver() = default;
    Screen_saver(const Screen_saver& t_to_copy) = default;
    Screen_saver(Screen_saver&& t_to_move) noexcept = default;
    Screen_saver& operator = (const Screen_saver& t_to_copy) = default;
    Screen_saver& operator = (Screen_saver&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_SCREEN_SAVER_MENU_HPP
