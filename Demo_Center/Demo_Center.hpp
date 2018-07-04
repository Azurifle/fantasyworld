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
      KEY_NO_PRESS, KEY_ESC = 27
      , OPTION_1 = '1', OPTION_2, OPTION_3, OPTION_4, OPTION_5, OPTION_LAST
      , DEFAULT_DOUBLE_POINTS = 2
    };
    static const float PRECISION;

    static void start();

    static int wait_key();
    static void press_to_continue();
    static void print_centered_header(const std::string& t_header, char t_delim);
    static std::string double_points_string(double t_double
      , int t_points = DEFAULT_DOUBLE_POINTS);

    ~Demo_center() = default;
  private:
    static void disable_mouse_editing();
    static int get_key();
    static void clear_2_nd_key_if_has();

    static void show_menu();
    static bool choose_option();
    static void do_option(int t_option = OPTION_LAST);
    static void demo_3_logger_n_stopwatch();
    
    static void demo_6_glfw();
    static void draw_triangle();
    static void paint_pos(float t_x, float t_y, float t_red = 0, float t_green = 0, float t_blue = 0);

    static void back_to_main_menu();

    Demo_center() = default;
    Demo_center(const Demo_center& t_to_copy) = default;
    Demo_center(Demo_center&& t_to_move) noexcept = default;
    Demo_center& operator = (const Demo_center& t_to_copy) = default;
    Demo_center& operator = (Demo_center&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_DEMO_CENTER_HPP