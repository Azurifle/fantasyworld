#include "stdafx.h"
#include "Menu_ui.hpp"
#include "World.hpp"//.cpp include .hpp & .hpp forward declare if not inheritance

namespace G6037599
{
  //___ (de)constructors _____________________________________________
  Menu_ui::~Menu_ui()
  {
    puts("menu UI destroyed.");
  }

  //___ public _____________________________________________
  int Menu_ui::main_menu()
  {
    do
    {
      main_menu_topic();
      const enum Option
      {
        NOT_ASSIGN = -1, OPTION_0_EXIT, OPTION_1, OPTION_2, OPTION_3
      };
      std::cout << "Input <" << OPTION_1 << " - " << OPTION_3 << "> or <" << OPTION_0_EXIT << "> to exit: ";
      int choice = NOT_ASSIGN;
      do
      {
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        switch (choice)
        {
        case OPTION_1: system("CLS");
          fantasy_world();
          back_to_main_menu();
          break;
        case OPTION_2: system("CLS");
          fantasy_world_2_d();
          back_to_main_menu();
          break;
        case OPTION_3: system("CLS");
          hero_in_fantasy_world();
          back_to_main_menu();
          break;

        case OPTION_0_EXIT: puts("");
          puts(" === End of program. =======================");
          press_any_key();
          return OPTION_0_EXIT;
        default: puts("");
          std::cout << "Please input only <" << OPTION_1 << " - " << OPTION_3
            << "> or <" << OPTION_0_EXIT << "> to exit: ";
        }
      } while (choice < OPTION_0_EXIT || choice > OPTION_3);
      system("CLS");
    } while (true);
  }

  /*COORD Menu_ui::get_cursor()
  {
    CONSOLE_SCREEN_BUFFER_INFO console_info;
    if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &console_info))
    {
      return console_info.dwCursorPosition;
    }
    return {0, 0};
  }

  void Menu_ui::set_cursor(const int t_y, const int t_x)
  {
    PROMISE(SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {t_x, t_y}));
  }*/

  int Menu_ui::limit_interval(int t_number, const int t_low, const int t_high)
  {
    if (t_number < t_low)
      t_number = t_low;
    else if (t_number > t_high)
      t_number = t_high;
    return t_number;
  }

  //___ Private ____________________________________________________________________________
  char Menu_ui::press_any_key()
  {
    const char key = _getch();
    _getch();
    return key;
  }

  void Menu_ui::main_menu_topic()
  {
    puts(" === Game Engine Fantasy World Projects =======================");
    puts("By: Darlyn Sirikasem G6037599");
    puts("");
    puts("");
    puts("         /////////////////////// Project list /////////////////////////////");
    puts("");
    puts("                    1. Fantasy World.");
    puts("");
    puts("                    2. Fantasy World 2D Grid + Code Refactor 1.");
    puts("");
    puts("                    3. A Hero in the Fantasy World.");
    puts("");
    puts("         //////////////////////////////////////////////////////////////////");
    puts("");
    puts("");
  }

  void Menu_ui::back_to_main_menu()
  {
    std::cout << std::endl
      << "Input <Any key> to main menu: ";
    press_any_key();
  }

  //___ Projects ____________________________________________________________________________
  void Menu_ui::fantasy_world()
  {
    puts(" === Fantasy World. =======================");
    const auto MONSTERS = 120, HERO_MAX_HP = 500;
    World world(MONSTERS);//Stack Overflow people suggest using stack over heap
    puts("");
    world.print_monster_list();
    puts("");
    world.create_player("NoOne the hero", HERO_MAX_HP);
    std::cout << std::endl << "Press <Any key> to update: ";
    press_any_key();
    puts("");
    world.update();
  }

  void Menu_ui::fantasy_world_2_d()
  {
    const auto TOPIC = " === Fantasy World 2D Grid. =======================";
    puts(TOPIC);
    puts("");
    const auto SIZE = 30, MONSTERS = 10;
    World world(SIZE, SIZE, MONSTERS);
    while (true)
    {
      puts("");
      world.build_grid();
      std::cout << std::endl
        << "Press <Any key> to update or <0> to exit: ";
      switch (press_any_key())
      {
      case '0': puts("");
        return;
      default: break;
      }
      system("CLS");
      puts(TOPIC);
      puts("");
      std::cout << "World " << SIZE << "x" << SIZE << " grid with "
        << MONSTERS << " monsters spawn randomly." << std::endl;
      puts("");
      world.update();
    }
  }

  void Menu_ui::hero_in_fantasy_world()
  {
    const auto TOPIC = " === A Hero in the Fantasy World. =======================";
    puts(TOPIC);
    puts("");
    const auto SIZE = 30, MONSTERS = 10, HERO_MAX_HP = 500, HERO_ATTACK_DAMAGE = 1;
    World world(SIZE, SIZE, MONSTERS);
    puts("");
    world.create_player("NoOne the hero", HERO_MAX_HP, "Fist !", HERO_ATTACK_DAMAGE);
    while (true)
    {
      puts("");
      world.build_grid();
      std::cout << std::endl
        << "Press <W/S/A/D>: Move, <Other key>: Attack same tile, or <0>: Exit.";
      switch (press_any_key())
      {
      case 'w': world.player_move(0, -1);
        break;
      case 's': world.player_move(0, 1);
        break;
      case 'a': world.player_move(-1, 0);
        break;
      case 'd': world.player_move(1, 0);
        break;
      case '0': puts("");
        return;
      default: break;
      }
      system("CLS");
      puts(TOPIC);
      puts("");
      world.update();
    }
  }
}//G6037599