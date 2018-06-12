#include "stdafx.h"
#include "Game_engine.hpp"
#include "1._Fantasy_Game/Fantasy_game.hpp"
#include "2._Car_Game/Car_game.hpp"

namespace G6037599
{
  //___ static ___________________________________________________________
  void Game_engine::start()
  {
    srand(GetTickCount());

    while (true)
    {
      show_header();
      enum Option
      {
        NOT_ASSIGN = -1, OPTION_0_EXIT, OPTION_1, OPTION_LAST
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
          Fantasy_game::run();
          back_to_main_menu();
          break;
        case OPTION_LAST: system("CLS");
          Car_game::run();
          back_to_main_menu();
          break;

        case OPTION_0_EXIT: puts("");
          puts("============================ End of Program ====================================");
          _getch(); _getch();
          return;
        default: puts("");
          std::cout << "Please input only <" << OPTION_1 << " - " << OPTION_LAST
            << "> or <" << OPTION_0_EXIT << "> to exit: ";
        }
      } while (choice < OPTION_0_EXIT || choice > OPTION_LAST);
      system("CLS");
    }//menu loop
  }

  void Game_engine::limit_interval(int& t_number, const int t_min, const int t_max)
  {
    if (t_number < t_min)
      t_number = t_min;
    else if (t_number > t_max)
      t_number = t_max;
  }

  //___ static private ___________________________________________________________
  void Game_engine::show_header()
  {
    puts(" === Game Engine Project =======================");
    puts("");
    puts("By: Darlyn Sirikasem G6037599");
    puts("");
    puts("");
    puts("         ////////////////////////// Game list /////////////////////////////");
    puts("");
    puts("                    1. The Fantasy World - NoOne The Hero.");
    puts("");
    puts("                    2. Bit Autonomous Car.");
    puts("");
    puts("         //////////////////////////////////////////////////////////////////");
    puts("");
    puts("");
  }

  void Game_engine::back_to_main_menu()
  {
    std::cout << std::endl
      << "Input <Any key> to main menu: ";
    _getch(); _getch();
  }
}//G6037599