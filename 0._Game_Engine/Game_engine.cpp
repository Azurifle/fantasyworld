#include "stdafx.h"
#include "Game_engine.hpp"
#include "1._Fantasy_Game/Fantasy_game.hpp"
#include "2._Car_Game/Car_game.hpp"

namespace G6037599
{
  //___ static ___________________________________________________________
  void Game_engine::start()
  {
    disable_mouse_editing();
    srand(GetTickCount());

    while (true)
    {
      show_header();
      const char OPTION_1 = '1', OPTION_LAST = '2', ESC = 27;
      std::cout << "Press <" << OPTION_1 << " - " << OPTION_LAST << "> or [ESC] to exit: ";
      auto wrong_input = true;
      while (wrong_input)
      {
        switch (_getch())
        {
        case OPTION_1: _getch(); system("CLS");
          Fantasy_game::run();
          wrong_input = false;
          back_to_main_menu();
          break;
        case OPTION_LAST: _getch(); system("CLS");
          Car_game::run();
          wrong_input = false;
          back_to_main_menu();
          break;

        case ESC: _getch();
          puts("\n");
          puts("============================ End of Program ====================================");
          _getch(); _getch();
          return;
        default: _getch();
        }
      }//input loop
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
  void Game_engine::disable_mouse_editing()
  {
    DWORD prev_mode;
    PROMISE(GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &prev_mode));
    PROMISE(SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), prev_mode & ~ENABLE_QUICK_EDIT_MODE));
  }

  void Game_engine::show_header()
  {
    puts("=== Game Engine =======================");
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
      << "Press <Any key> to main menu: ";
    _getch(); _getch();
    system("CLS");
  }
}//G6037599