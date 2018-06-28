#ifndef G6037599_DEMO_CENTER_HPP
#define G6037599_DEMO_CENTER_HPP
#pragma once
#include "Week_10/Mat4.hpp"

namespace G6037599
{
  class Demo_center final
  {
  public:
    enum Enum
    {
      KEY_NO_PRESS, KEY_ESC = 27
      , OPTION_1 = '1', OPTION_2, OPTION_3, OPTION_4, OPTION_LAST
    };

    static void start();

    static int wait_key();
    static void press_to_continue();

    static void test_case(const std::string& t_operator
      , double t_actual, double t_expected);
    static void test_case(const std::string& t_operator
      , int t_actual, int t_expected);
    static void test_case(const std::string& t_operator
      , bool t_actual, bool t_expected);
    static void show_test_case(const std::string& t_operator
      , const std::string& t_expected, bool t_condition);
    static void print_centered_header(const std::string& t_header, char t_delim);

    static std::string double_to_2_points_string(double t_double);

    ~Demo_center() = default;    
  private:
    static void disable_mouse_editing();
    static void show_menu();
    static bool choose_option();
    static int get_key();
    static void clear_2_nd_key_if_has();
    static void do_option(int t_option = OPTION_LAST);
    static void demo_3_logger_n_stopwatch();
    static void demo_5_matrix_test_unit();
    static void mat4_test_case(const std::string& t_operator, const Mat4& t_actual
      , const Mat4& t_expected);
    static void back_to_main_menu();

    Demo_center() = default;
    Demo_center(const Demo_center& t_to_copy) = default;
    Demo_center(Demo_center&& t_to_move) noexcept = default;
    Demo_center& operator = (const Demo_center& t_to_copy) = default;
    Demo_center& operator = (Demo_center&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_DEMO_CENTER_HPP