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
        OPTION_0_EXIT, OPTION_1, OPTION_2, OPTION_3
      };
      std::cout << "Input <" << OPTION_1 << " - " << OPTION_3 << "> or <" << OPTION_0_EXIT << "> to exit: ";
      int choice = World::NOT_ASSIGN;
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

  COORD Menu_ui::get_cursor()
  {
    CONSOLE_SCREEN_BUFFER_INFO console_info;
    if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &console_info))
    {
      return console_info.dwCursorPosition;
    }
    return {0, 0};
  }

  void Menu_ui::move_cursor(const int t_y, const int t_x)
  {
    PROMISE(SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)
      , {static_cast<short>(t_x), static_cast<short>(t_y)}));
  }

  void Menu_ui::move_cursor(const COORD t_position)
  {
    PROMISE(SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), t_position));
  }

  int Menu_ui::limit_interval(int t_number, const int t_min, const int t_max)
  {
    if (t_number < t_min)
      t_number = t_min;
    else if (t_number > t_max)
      t_number = t_max;
    return t_number;
  }

  //___ Private ____________________________________________________________________________
  int Menu_ui::press_any_key()
  {
    const auto key = _getch();
    _getch();
    return key; 
  }

  int Menu_ui::wait_key(const int t_seconds)
  {
    const auto MAKE_MILLISECOND = 1000;
    const auto TIME_UP = clock() + t_seconds * MAKE_MILLISECOND;
    do
    {
      const auto NO_KEY_PRESS = 0;
      switch (_kbhit())
      {
      case NO_KEY_PRESS: break;
      default: return press_any_key();
      }
    } while (clock() < TIME_UP);

    return World::NOT_ASSIGN;
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
    puts("");
    std::cout << "Frame rate is " << UPDATE_SECONDS << " seconds per frame.";
    puts("");
    std::cout << std::endl << "Press <Any key> to update: ";
    press_any_key();

    while (true)
    {
      system("CLS");
      puts(TOPIC);
      puts("");
      world.update();
      puts("");
      world.build_grid();
      puts("");
      std::cout << "Update in " << UPDATE_SECONDS << " secs.";
      puts(" Press <Any key>: update now, or <0>: exit.");
      switch (wait_key(UPDATE_SECONDS))
      {
      case '0': return; default:;
      }
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
    puts("");
    std::cout << "frame rate is " << UPDATE_SECONDS << " seconds per frame.";
    puts("");
    std::cout << std::endl << "Press <Any key> to update: ";
    press_any_key();

    system("CLS");
    puts(TOPIC);
    puts("");
    world.build_console();
    puts("");
    world.build_grid();
    puts("");
    std::cout << "Update in " << UPDATE_SECONDS << " secs.";
    puts(" Press <W/S/A/D>: move, <Other key>: update now, or <0>: exit.");
    const auto LAST_LINE = get_cursor();
    enum Direction
    {
      UP = -1, LEFT = -1, NONE, DOWN, RIGHT = 1
    };
    while (true)
    {
      switch (wait_key(UPDATE_SECONDS))
      {
      case 'w': world.player_move(NONE, UP);
        break;
      case 's': world.player_move(NONE, DOWN);
        break;
      case 'a': world.player_move(LEFT, NONE);
        break;
      case 'd': world.player_move(RIGHT, NONE);
        break;
      case '0': move_cursor(LAST_LINE.Y, LAST_LINE.X);
        return; default:;
      }
      world.update();
    }
  }
}//G6037599