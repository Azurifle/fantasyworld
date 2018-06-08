// G6037599.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Week_1/Animal.hpp"
#include "Week_2/Memory_pool.hpp"
#include "Week_7/Logger.hpp"
#include "Week_7/Stopwatch.hpp"

void show_header();
void back_to_main_menu();

int main()
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  do
  {
    show_header();
    enum Option
    {
      NOT_ASSIGN = -1, OPTION_0_EXIT, OPTION_1, OPTION_2, OPTION_3, OPTION_LAST
    };
    std::cout << "Input <" << OPTION_1 << " - " << OPTION_LAST << "> or <" << OPTION_0_EXIT << "> to exit: ";
    int choice = NOT_ASSIGN;
    do
    {
      std::cin >> choice;
      std::cin.clear();
      std::cin.ignore(INT_MAX, '\n');
      switch (choice)
      {
      case OPTION_1: system("CLS");
        G6037599::oop_demo();
        back_to_main_menu();
        break;
      case OPTION_2: system("CLS");
        G6037599::memory_pool_demo();
        back_to_main_menu();
        break;
      case OPTION_3: system("CLS");
        G6037599::logger_demo();
        back_to_main_menu();
        break;
      case OPTION_LAST: system("CLS");
        G6037599::Stopwatch::demo();
        back_to_main_menu();
        break;

      case OPTION_0_EXIT: puts("");
        puts("============================ End of Program ====================================");
        _getch(); _getch();
        return OPTION_0_EXIT;
      default: puts("");
        std::cout << "Please input only <" << OPTION_1 << " - " << OPTION_LAST
          << "> or <" << OPTION_0_EXIT << "> to exit: ";
      }
    } while (choice < OPTION_0_EXIT || choice > OPTION_LAST);
    system("CLS");
  } while (true);
}

void show_header()
{
  puts(" === Game Engine Projects =======================");
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
  puts("         //////////////////////////////////////////////////////////////////");
  puts("");
  puts("");
}

void back_to_main_menu()
{
  std::cout << std::endl
    << "Input <Any key> to main menu: ";
  _getch(); _getch();
}