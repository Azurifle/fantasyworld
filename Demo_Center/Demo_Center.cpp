#include "stdafx.h"
#include "Demo_Center.hpp"
#include "Week_1/Dog.hpp"
#include "Week_2/Memory_pool.hpp"
#include "Week_7/Logger.hpp"
#include "Week_7/Stopwatch.hpp"
#include "Week_9/Vec_test_units.hpp"
#include "Week_10/Mat4.hpp"

namespace G6037599
{
  // ___ static ___________________________________________________________
  void Demo_center::start()
  {
    static auto is_running = false;
    REQUIRE(!is_running);
    is_running = true;

    disable_mouse_editing();

    while (true)
    {
      show_menu();
      std::cout << "Press <" << static_cast<char>(OPTION_1) << " - "
        << static_cast<char>(OPTION_LAST) << "> or [ESC] to exit: ";
      switch (is_running = choose_option())
      {
      case false: return; default:;
      }
    }
  }

  int Demo_center::wait_key()
  {
    const auto FIRST_KEY = _getch();
    clear_2_nd_key_if_has();
    return FIRST_KEY;
  }

  void Demo_center::press_to_continue()
  {
    puts("");
    const std::string HINT("Press <Any key> to continue: ");
    std::cout << HINT.c_str();
    wait_key();
    std::cout << '\r' << std::setw(HINT.size()) << std::setfill(' ')
      << ' ' << '\r';
  }

  void Demo_center::test_case(const std::string& t_operator, const int t_actual
    , const int t_expected)
  {
    show_test_case(t_operator, std::to_string(t_expected)
      , t_actual == t_expected);
  }

  void Demo_center::test_case(const std::string& t_operator, const double t_actual
    , const double t_expected)
  {
    const auto PRECISION = 0.01;
    show_test_case(t_operator, double_to_2_points_string(t_expected)
      , abs(t_actual - t_expected) <= PRECISION);
  }

  void Demo_center::test_case(const std::string& t_operator, const bool t_actual
    , const bool t_expected)
  {
    show_test_case(t_operator, t_expected ? "true" : "false"
      , t_actual == t_expected);
  }

  void Demo_center::show_test_case(const std::string& t_operator
    , const std::string& t_expected, const bool t_condition)
  {
    std::cout << "  " << t_operator.c_str() << " == " << t_expected.c_str()
      << " ?: " << (t_condition ? "Pass" : "Fail")
      << '.' << std::endl;
  }

  void Demo_center::print_centered_header(const std::string& t_header, const char t_delim)
  {
    const unsigned MAX_HEADER_COLS = 80
      , SPACE_BEFORE = (MAX_HEADER_COLS - t_header.length()) / 2
      , SPACE_AFTER = SPACE_BEFORE + SPACE_BEFORE % 2;
    std::cout << std::setw(SPACE_BEFORE-1) << std::setfill(t_delim) << t_delim;
    std::cout << ' ' << t_header << ' ' 
      << std::setw(SPACE_AFTER-1) << std::setfill(t_delim) << t_delim << std::endl 
      << std::endl;
  }

  std::string Demo_center::double_to_2_points_string(const double t_double)
  {
    std::stringstream double_2_decimal_points;
    double_2_decimal_points << std::fixed << std::setprecision(2)
      << t_double;
    return double_2_decimal_points.str();
  }

  // ___ private static ____________________________________________________
  void Demo_center::disable_mouse_editing()
  {
    DWORD prev_mode;
    PROMISE(GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &prev_mode));
    PROMISE(SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), prev_mode & ~ENABLE_QUICK_EDIT_MODE));
  }

  void Demo_center::show_menu()
  {
    puts(" === Game Engine Other Projects =======================");
    puts("");
    puts("By: Darlyn Sirikasem G6037599");
    puts("");
    puts("");
    puts("         /////////////////////// Project list /////////////////////////////");
    puts("");
    puts("               1. Week 1 Object Oriented Programming.");
    puts("");
    puts("               2. Week 2 Memory Manager.");
    puts("");
    puts("               3. Week 7 Singleton Logger & High-Resolution Stopwatch.");
    puts("");
    puts("               4. Week 9 Vec 2 - 4D <template>.");
    puts("");
    puts("               5. Week 10 Matrix 4x4D of float.");
    puts("");
    puts("         //////////////////////////////////////////////////////////////////");
    puts("");
    puts("");
  }

  bool Demo_center::choose_option()
  {
    while (true)
    {
      const auto OPTION = get_key();
      if (OPTION_1 <= OPTION && OPTION <= OPTION_LAST)
      {
        do_option(OPTION);
        return true;
      }

      switch (OPTION)
      {
      case KEY_ESC: return false; default:;
      }
    }
  }

  int Demo_center::get_key()
  {
    switch (_kbhit())
    {
    case KEY_NO_PRESS: return KEY_NO_PRESS;
    default: return wait_key();
    }
  }

  void Demo_center::clear_2_nd_key_if_has()
  {
    switch (_kbhit())
    {
    case KEY_NO_PRESS: break;
    default: _getch();
    }
  }

  void Demo_center::do_option(const int t_option)
  {
    system("CLS");
    switch (t_option)
    {
    case OPTION_1: demo_oop(); break;
    case OPTION_2: demo_memory_pool(); break;
    case OPTION_3: demo_3_logger_n_stopwatch(); break;
    case OPTION_4: Vec_test_units::run(); break;
    default: demo_5_matrix_test_unit();
    }
    back_to_main_menu();
  }

  void Demo_center::demo_3_logger_n_stopwatch()
  {
    logger_demo();
    press_to_continue();
    Stopwatch::demo();
  }

  void Demo_center::demo_5_matrix_test_unit()
  {
    print_centered_header("Matrix Test Unit", '=');

    mat4_test_case("A matrix of zeros", Mat4(), Mat4(0));
    mat4_test_case("An identity matrix", Mat4::identity(), Mat4(1));
  }

  void Demo_center::mat4_test_case(const std::string& t_operator
    , const Mat4& t_actual, const Mat4& t_expected)
  {
    show_test_case(t_operator, "Mat4" + t_expected.to_string()
      , t_actual == t_expected);
  }

  void Demo_center::back_to_main_menu()
  {
    std::cout << std::endl
      << " ======================== End of Demo =========================="
      << std::endl << std::endl
      << "Press <Any key> to main menu: ";
    wait_key();
    system("CLS");
  }
}//G6037599