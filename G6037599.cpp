// G6037599.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Week_1/Animal.hpp"
#include "Week_2/Memory_pool.hpp"
#include "Week_7/Logger.hpp"
#include "Week_7/Stopwatch.hpp"
#include "Week_9/Vec2_i.hpp"

void show_header();
void back_to_main_menu();

const int KEY_NO_PRESS = 0;

int wait_key();

int get_key()
{
  switch (_kbhit())
  {
  case KEY_NO_PRESS: return KEY_NO_PRESS;
  default: return wait_key();
  }//switch 1st keyboard hit
}

int wait_key()
{
  const auto FIRST_KEY = _getch();
  switch (FIRST_KEY)
  {
  default: switch (_kbhit())
  {
  case KEY_NO_PRESS: break;
  default: _getch();
  }//switch 2nd keyboard hit
           return FIRST_KEY;
  }
}


int main()
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  while (true)
  {
    show_header();
    enum Option
    {
      ESC = 27, OPTION_1 = '1', OPTION_2, OPTION_3, OPTION_4, OPTION_LAST
    };
    std::cout << "Press <" << static_cast<char>(OPTION_1) 
      << " - " << static_cast<char>(OPTION_LAST) << "> or [ESC] to exit: ";
    auto wrong_input = true;
    while (wrong_input)
    {
      switch (get_key())
      {
      case OPTION_1: system("CLS");
        G6037599::oop_demo();
        wrong_input = false;
        back_to_main_menu();
        break;
      case OPTION_2: system("CLS");
        G6037599::memory_pool_demo();
        wrong_input = false;
        back_to_main_menu();
        break;
      case OPTION_3: system("CLS");
        G6037599::logger_demo();
        wrong_input = false;
        back_to_main_menu();
        break;
      case OPTION_4: system("CLS");
        G6037599::Stopwatch::demo();
        wrong_input = false;
        back_to_main_menu();
        break;
      case OPTION_LAST: system("CLS");
        G6037599::vec2_i_demo();
        wrong_input = false;
        back_to_main_menu();
        break;

      case ESC: return 0;
      default:;
      }
    }//input loop
  }//menu loop
}

void show_header()
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
  puts("                    5. Week 9 Vec2.");
  puts("");
  puts("         //////////////////////////////////////////////////////////////////");
  puts("");
  puts("");
}

void back_to_main_menu()
{
  std::cout << std::endl
    << "Press <Any key> to main menu: ";
  wait_key();
  system("CLS");
}