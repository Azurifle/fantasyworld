#include "stdafx.h"
#include "Demo_Center.hpp"
#include "Week_1/Dog.hpp"
#include "Week_2/Memory_pool.hpp"
#include "Week_7/Logger.hpp"
#include "Week_7/Stopwatch.hpp"
#include "Week_9/Vec2_i.hpp"

// ___ static ___________________________________________________________
void G6037599::Demo_center::start()
{
  REQUIRE(!m_is_running_);
  m_is_running_ = true;

  disable_mouse_editing();

  while (true)
  {
    show_header();
    std::cout << "Press <" << static_cast<char>(OPTION_1) << " - " 
      << static_cast<char>(OPTION_LAST) << "> or [ESC] to exit: ";
    switch (choose_option())
    {
    case false: return; default:;
    }
  }
}

int G6037599::Demo_center::wait_key()
{
  const auto FIRST_KEY = _getch();
  clear_2_nd_key_if_has();
  return FIRST_KEY;
}

// ___ private static ____________________________________________________
bool G6037599::Demo_center::m_is_running_ = false;

// ___ private ___________________________________________________________
void G6037599::Demo_center::disable_mouse_editing()
{
  DWORD prev_mode;
  PROMISE(GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &prev_mode));
  PROMISE(SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), prev_mode & ~ENABLE_QUICK_EDIT_MODE));
}

void G6037599::Demo_center::show_header()
{
  puts(" === Game Engine Other Projects =======================");
  puts("");
  puts("By: Darlyn Sirikasem G6037599");
  puts("");
  puts("");
  puts("         /////////////////////// Project list /////////////////////////////");
  puts("");
  puts("                    1. Week 1 Object Oriented Programming.");
  puts("");
  puts("                    2. Week 2 Memory Manager.");
  puts("");
  puts("                    3. Week 7 Singleton Logger.");
  puts("");
  puts("                    4. Week 7 High-Resolution-Time Stopwatch.");
  puts("");
  puts("                    5. Week 9 Vec2i.");
  puts("");
  puts("         //////////////////////////////////////////////////////////////////");
  puts("");
  puts("");
  //puts("                    5. Week 9 Vec 2 - 4 & Matrix <template>.");
}

bool G6037599::Demo_center::choose_option()
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

int G6037599::Demo_center::get_key()
{
  switch (_kbhit())
  {
  case KEY_NO_PRESS: return KEY_NO_PRESS;
  default: return wait_key();
  }
}

void G6037599::Demo_center::clear_2_nd_key_if_has()
{
  switch (_kbhit())
  {
  case KEY_NO_PRESS: break;
  default: _getch();
  }
}

void G6037599::Demo_center::do_option(const int t_option)
{
  system("CLS");
  switch (t_option)
  {
  case OPTION_1: oop_demo(); break;
  case OPTION_2: memory_pool_demo(); break;
  case OPTION_3: logger_demo(); break;
  case OPTION_4: Stopwatch::demo();  break;
  default: vec2_i_test_unit();
  }
  back_to_main_menu();
}

void G6037599::Demo_center::back_to_main_menu()
{
  std::cout << std::endl
    << " ======================== End of Demo ==========================" 
    << std::endl << std::endl
    << "Press <Any key> to main menu: ";
  wait_key();
  system("CLS");
}