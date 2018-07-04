#include "stdafx.h"
#include "Demo_Center.hpp"
#include "Week_01/Dog.hpp"
#include "Week_02/Memory_pool.hpp"
#include "Week_07/Logger.hpp"
#include "Week_07/Stopwatch.hpp"
#include "Week_09/Vec_test_units.hpp"
#include "Test_units.hpp"

namespace G6037599
{
  // ___ static ___________________________________________________________
  const float Demo_center::PRECISION = 0.01f;

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

  std::string Demo_center::double_points_string(const double t_double, const int t_points)
  {
    std::stringstream double_w_points;
    double_w_points << std::fixed << std::setprecision(t_points) << t_double;
    return double_w_points.str();
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
    puts("               5. Week 10 Matrix 4x4 of float.");
    puts("");
    puts("               6. Week 11 GLFW.");
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
    case OPTION_5: Test_units::mat4_test_unit(); break;
    default: demo_6_glfw();
    }
    back_to_main_menu();
  }

  // ___ demo_3_logger_n_stopwatch ____________________________________________________
  void Demo_center::demo_3_logger_n_stopwatch()
  {
    logger_demo();
    press_to_continue();
    Stopwatch::demo();
  }

  // ___ demo_6_glfw ____________________________________________________
  void Demo_center::demo_6_glfw()
  {
    if(!glfwInit())
    {
      glfwTerminate();
      return;
    }

    const auto WINDOW_WIDTH = 640, WINDOW_HEIGHT = 480;
    const auto WINDOW = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Game", nullptr, nullptr);
    if (!WINDOW)
    {
      glfwTerminate();
      return;
    }

    glfwMakeContextCurrent(WINDOW);

    const auto ROTATE_SPEED = 0.1f;
    auto rotation = 0.0f;
    while (!glfwWindowShouldClose(WINDOW))
    {
      glClear(GL_COLOR_BUFFER_BIT);
      glClearColor(0, 0, 1, 1);

      draw_triangle();

      glfwSwapBuffers(WINDOW);
      glfwPollEvents();

      rotation += ROTATE_SPEED;
    }//game loop
    glfwTerminate();
  }
  /*
  void key_callback(GLFWwindow* t_window, const int t_key
    , const int t_scan_code, const int t_action)
  {
    if(t_key == GLFW_KEY_E && t_action == GLFW_PRESS)
    {
      std::cout << "I press E" << std::endl;
    }
  }
  */
  void Demo_center::draw_triangle()
  {
    glBegin(GL_TRIANGLES);
      paint_pos(-1, 0, 1);
      paint_pos(0, 1, 1, 0, 1);
      paint_pos(1, 0, 0, 1, 0);
    glEnd();
  }

  void Demo_center::paint_pos(const float t_x, const float t_y
    , const float t_red, const float t_green, const float t_blue)
  {
    glColor3f(t_red, t_green, t_blue);
    glVertex3f(t_x, t_y, 0);
  }

  // ___ back_to_main_menu ____________________________________________________
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