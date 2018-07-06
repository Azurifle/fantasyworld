#ifndef G6037599_DEMO_CENTER_HPP
#define G6037599_DEMO_CENTER_HPP
#pragma once

namespace G6037599
{
  class Demo_center final
  {
  public:
    enum Enum
    {
      KEY_NO_PRESS, KEY_ESC = 27, DEFAULT_DOUBLE_POINTS = 2
    };
    static const float PRECISION;

    static void disable_mouse_editing();
    static int get_key();
    static int wait_key();
    static void press_to_continue();
    static void print_centered_header(const std::string& t_header, char t_delim);
    static std::string double_points_string(double t_double
      , int t_points = DEFAULT_DOUBLE_POINTS);

    static void reset_delta_seconds();
    static float delta_seconds();

    ~Demo_center() = default;
  private:
    using Clock = std::chrono::high_resolution_clock;
    using Float_seconds = std::chrono::duration<float>;

    static Float_seconds m_delta_seconds_;

    static void clear_2_nd_key_if_has();

    Demo_center() = default;
    Demo_center(const Demo_center& t_to_copy) = default;
    Demo_center(Demo_center&& t_to_move) noexcept = default;
    Demo_center& operator = (const Demo_center& t_to_copy) = default;
    Demo_center& operator = (Demo_center&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_DEMO_CENTER_HPP